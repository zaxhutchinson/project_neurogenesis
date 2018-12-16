#include"InputVector.hpp"

InputVector::InputVector() {

}
InputVector::InputVector(int size) {
    for(int i = 0; i < size; i++) {
        inputs.push_back(std::make_shared<double>(0.0));
    }
}

void InputVector::SetInputs(vec<double> & values) {
    for(int i = 0; i < values.size(); i++) {
        *(inputs[i]) = values[i];
    }
}
void InputVector::SetInput(int position, double signal) {
    *(inputs[position]) = signal;
}

void InputVector::ZeroInputs() {
    for(int i = 0; i < inputs.size(); i++) {
        (*inputs[i]) = 0.0;
    }
}

vsptr<double> & InputVector::GetInputs() {
    return inputs;
}