#include <iostream>
#include <argparse/argparse.hpp>
#include <parameter/parameter_reader.hpp>

struct CmdArguments {
    std::string format;
    std::string instance_file;
};

inline argparse::ArgumentParser createArgumentParser(int argc, char** argv) {
    argparse::ArgumentParser program(argv[0], "1.0");

    program.add_argument("-f", "--format")
        .help("format of the instance file [options: \"AP\", \"CAB\"]")
        .nargs(1)
        .default_value(std::string{"AP"})
        .action([](const std::string& value) {
            static const std::array<std::string, 3> choices = { "AP", "CAB" };
            if(std::find(choices.cbegin(), choices.cend(), value) != choices.cend()) {
                return value;
            } else {
                throw std::runtime_error("format value \"" + value + "\" not supported");
            }
        });
    
    program.add_argument("instance_file")
        .help("instance file path");
    
    return program;
}


int main(int argc, char** argv) {
    auto program = createArgumentParser(argc, argv);

    try {
        program.parse_args(argc, argv);

    } catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    CmdArguments args{program.get("format"), program.get("instance_file")};
    
    return 0;
}
