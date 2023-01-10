#ifndef __CPP_EDITOR_OPEN_HPP_
#define __CPP_EDITOR_OPEN_HPP_
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

namespace cpp_editor_tool { 
    std::string generateRandomString(int length) {
        std::string str;
        std::srand(time(nullptr));
        for (int i = 0; i < length; i++) {
            char c = static_cast<char>(rand() % 26 + 'a');
            str += c;
        }
        return str;
    };
};
namespace cpp_editor_class { 
    class Class {
      public:
        void setPath(std::string path){
            this->path = path;
        };
        void setExt(std::string ext){
            this->extension = ext;
        };
        void setEditor(std::string ed){
            this->editor_cmd = ed;
        };
        std::string editor(std::string text){
            this->fileName();
            this->fileWrite(text);
            this->open();
            text = this->fileRead();
            std::filesystem::remove(this->file_path);
            return text;
        };
      private:
        std::string path = "/tmp/";
        std::string extension = ".txt";
        std::string file_path = "";
        std::string editor_cmd = "vim";

        std::string fileRead (){
            auto ss = std::ostringstream{};
            ss << std::ifstream(this->file_path).rdbuf();
            std::string text =  ss.str();
            return text;
        };
        void fileWrite(
          std::string text
        ){
            std::ofstream prefile (this->file_path); 
            if (!prefile.is_open())
                return;
            prefile << text;
            prefile.close();
        };
        void open(){
            std::system(
              (
                this->editor_cmd+
                " "+
                this->file_path
              ).c_str()
            );
        };
        void fileName(){
            this->file_path = (
                this->path+
                cpp_editor_tool::generateRandomString(10)+
                "."+
                this->extension
            );

        };
    };
};
namespace cpp_editor_sec {
    cpp_editor_class::Class *editor = new cpp_editor_class::Class();
}; 

namespace cppEditor {
    void setPath(
      std::string path
    ){
        cpp_editor_sec::editor->setPath(path);
    };
    void setExt(
      std::string extension
    ){
        cpp_editor_sec::editor->setExt(extension);
    };
    void setEditor(
      std::string ed
    ){
        cpp_editor_sec::editor->setEditor(ed);
    };
    std::string editor(
      std::string text
    ){
        return cpp_editor_sec::editor->editor(text);
    };
};

#endif
