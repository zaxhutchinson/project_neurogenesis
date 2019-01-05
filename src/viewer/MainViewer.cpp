
#include"cereal/cereal.hpp"
#include"cereal/archives/binary.hpp"

#include"zxlb.hpp"
#include"Model.hpp"

void Save(std::string filename, sptr<Model> model);
sptr<Model> Load(std::string filename);  

int main() {

    uptr<Model> model;

    return 0;
}

void Save(std::string filename, sptr<Model> model) {
    std::cout << "SAVING TO: " << filename << std::endl;
    std::ofstream out(filename, std::ios::binary | std::ios::out);
    cereal::BinaryOutputArchive oarchive(out);
    oarchive(model);
}

sptr<Model> Load(std::string filename) {
    sptr<Model> model;
    std::cout << "LOADING FROM: " << filename << std::endl;
    std::ifstream in(filename, std::ios::binary | std::ios::in);
    cereal::BinaryInputArchive iarchive(in);
    iarchive(model);
    return model;
}