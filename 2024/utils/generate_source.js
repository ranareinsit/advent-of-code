import fs from 'fs';
import readline from 'readline';

const mkCMakeList = (name) => {
    let template = `
#
add_library(day_${name} STATIC "src/common.cpp")

#
add_executable(day_${name}_part_01_exec "src/part_01.cpp")
target_link_libraries(day_${name}_part_01_exec PRIVATE day_${name})

#
add_executable(day_${name}_part_02_exec "src/part_02.cpp")
target_link_libraries(day_${name}_part_02_exec PRIVATE day_${name})

#
add_custom_command(TARGET day_${name} POST_BUILD
    COMMAND \$\{CMAKE_COMMAND\} -E copy_if_different
        \$\{CMAKE_SOURCE_DIR\}/src/lib/day_${name}/src/input.txt
        \$\{CMAKE_BINARY_DIR\}/src/lib/day_${name}/src/input.txt
)

#
add_custom_command(TARGET day_${name} POST_BUILD
    COMMAND \$\{CMAKE_COMMAND\} -E copy_if_different
        \$\{CMAKE_SOURCE_DIR\}/src/lib/day_${name}/src/test-input.txt
        \$\{CMAKE_BINARY_DIR\}/src/lib/day_${name}/src/test-input.txt
)

#
target_include_directories(day_${name}
        PUBLIC
        $<BUILD_INTERFACE:\$\{CMAKE_CURRENT_SOURCE_DIR\}/include>
        $<INSTALL_INTERFACE:include>
)

install(TARGETS day_${name}
        EXPORT day_${name}Config
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
install(EXPORT day_${name}Config DESTINATION share/day_${name}/cmake)
export(TARGETS day_${name} FILE day_${name}Config.cmake)
`.trim();
    return template;
};

const mkCommonHeader = name => `
#pragma once
namespace day_${name} {};
`.trim();

const mkCommonFile = name => `namespace day_${name} {}`.trim();

const mkPart = name => {
    return `
    #include <day_${name}/common.hpp>
    int main() {return 0;}
    `.trim();
};

const testCmakeList = name => {
    let template = `
    find_package(Catch2 REQUIRED)
    
    add_executable(day_${name}_tests "day_${name}.cpp")
    
    # Test framework dependencies.
    target_link_libraries(day_${name}_tests         PRIVATE Catch2::Catch2WithMain)
    
    # Functionality to test.
    target_link_libraries(day_${name}_tests         PRIVATE day_${name})
    
    add_test(NAME day_${name}_tests_name COMMAND day_${name}_tests )
    
    # copy input files for each test
    add_custom_command(TARGET day_${name}_tests  POST_BUILD
        COMMAND \$\{CMAKE_COMMAND\} -E copy_if_different
            \$\{CMAKE_SOURCE_DIR\}/src/lib/day_${name}/src/input.txt
            \$\{CMAKE_CURRENT_BINARY_DIR\}/input.txt
        COMMAND \$\{CMAKE_COMMAND\} -E copy_if_different
            \$\{CMAKE_SOURCE_DIR\}/src/lib/day_${name}/src/test-input.txt
            \$\{CMAKE_CURRENT_BINARY_DIR\}/test-input.txt
    )
    `.trim();
    return template;
};

const mkTestFile = name => `
#include <catch2/catch_test_macros.hpp>

#include <day_${name}/common.hpp>

TEST_CASE("empty", "[day_${name}]")
{
	CHECK(true);
}
`.trim();

// TODO: generate project layout

function layout(name) {
    // --- folders
    // src
    fs.mkdirSync(`./src/lib/day_${name}`);
    fs.mkdirSync(`./src/lib/day_${name}/include/`);
    fs.mkdirSync(`./src/lib/day_${name}/include/day_${name}`);
    fs.mkdirSync(`./src/lib/day_${name}/src/`);
    // test
    fs.mkdirSync(`./src/tests/day_${name}`);

    // --- files
    // cmake
    fs.writeFileSync(`./src/lib/day_${name}/CMakeLists.txt`, mkCMakeList(name));
    // header
    fs.writeFileSync(`./src/lib/day_${name}/include/day_${name}/common.hpp`, mkCommonHeader(name));
    // src
    fs.writeFileSync(`./src/lib/day_${name}/src/common.cpp`, mkCommonFile(name));
    fs.writeFileSync(`./src/lib/day_${name}/src/part_01.cpp`, mkPart(name));
    fs.writeFileSync(`./src/lib/day_${name}/src/part_02.cpp`, mkPart(name));
    fs.writeFileSync(`./src/lib/day_${name}/src/input.txt`, ``);
    fs.writeFileSync(`./src/lib/day_${name}/src/test-input.txt`, ``);
    fs.writeFileSync(`./src/lib/day_${name}/README.md`, `#\n#`);
    // tests
    fs.writeFileSync(`./src/tests/day_${name}/CMakeLists.txt`, testCmakeList(name));
    fs.writeFileSync(`./src/tests/day_${name}/day_${name}.cpp`, mkTestFile(name));

    // addition into top cmake tests

}

function formatArgument(arg) {
    const num = parseInt(arg, 10);
    return isNaN(num)
        ? arg
        : (num.toString().length === 1
            ? `0${num}`
            : num.toString());
}

function modifyTopCMake(name, filePath = `./CMakeLists.txt`) {
    let data = fs.readFileSync(filePath, 'utf8');
    const regex = /if\(BUILD_TESTING\)[\s\S]*?endif\(\)/;
    data = data.replace(regex, match => {
        const updatedMatch = match.replace('endif()', `  add_subdirectory(src/tests/day_${name})\nendif()`);
        return updatedMatch;
    });

    const regex2 = /if\(BUILD_TESTING\)/;
    data = data.replace(regex2, match => {
        return `add_subdirectory(src/lib/day_${name})\n\n${match}`;
    });

    fs.writeFileSync(filePath, data, 'utf8');
}

function modifyTopReadme(name, filePath = `../README.md`) {
    let data = fs.readFileSync(filePath, 'utf8');

    data += `\n[Day ${name}](./2024/src/lib/day_${name}/README.md)`

    fs.writeFileSync(filePath, data, 'utf8');
}

function askUser(question) {
    return new Promise(resolve => rl.question(question, resolve));
}



const args = process.argv.slice(2);

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});


async function main() {
    console.log(`working on:`, process.cwd());
    for (let arg of args) {
        let name = formatArgument(arg);
        console.log(`creating: `, name);
        const confirm = await askUser('Do you want to create the file? (y/n) ');
        if (confirm.toLowerCase() !== 'y') {
            console.log('Operation aborted');
            rl.close();
            return;
        }
        await layout(formatArgument(name));
        console.log(`adding into cmake: `, name);
        await modifyTopCMake(name);
        await modifyTopReadme(name)
    }
    rl.close();
}

main();
