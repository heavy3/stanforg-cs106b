// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue(): patientNames(), patientPriority() {
    // TODO: write this constructor
}

VectorPatientQueue::~VectorPatientQueue() {
    // TODO: write this destructor
}

void VectorPatientQueue::clear() {
    // TODO: write this function
    patientNames.clear();
    patientPriority.clear();
}

string VectorPatientQueue::frontName() {
    // TODO: write this function
    if (patientNames.isEmpty()) {
        throw std::length_error("No patients");
    }

    int minPriority = 8;
    int minIndex = 0;
    for (int i = 0; i < patientPriority.size(); i++) {
        if (patientPriority[i] < minPriority) {
            minPriority = patientPriority[i];
            minIndex = i;
        }
    }
    return patientNames[minIndex];
}

int VectorPatientQueue::frontPriority() {
    // TODO: write this function
    if (patientNames.isEmpty()) {
        throw std::length_error("No patients");
    }

    int minPriority = 8;
    for (int i = 0; i < patientPriority.size(); i++) {
        if (patientPriority[i] < minPriority) {
            minPriority = patientPriority[i];
        }
    }
    return minPriority;
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    return patientNames.isEmpty();   // this is only here so it will compile
}

void VectorPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    patientNames.add(name);
    patientPriority.add(priority);
}

string VectorPatientQueue::processPatient() {
    // TODO: write this function
    if (patientNames.isEmpty()) {
        throw std::length_error("No patients");
    }

    int minPriority = 8;
    int minIndex = 0;
    for (int i = 0; i < patientPriority.size(); i++) {
        if (patientPriority[i] < minPriority) {
            minPriority = patientPriority[i];
            minIndex = i;
        }
    }

    string name = patientNames[minIndex];
    patientNames.remove(minIndex);
    patientPriority.remove(minIndex);
    return name;
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    int minPriority = 8;
    int patientIndex = -1;
    for (int i = 0; i < patientPriority.size(); i++) {
        if (patientNames[i] == name && patientPriority[i] < minPriority) {
            patientIndex = i;
            minPriority = patientPriority[i];
        }
    }

    if (patientIndex == -1)
        throw std::invalid_argument("name not exit");
    patientPriority[patientIndex] = newPriority;
}

string VectorPatientQueue::toString() {
    // TODO: write this function
    string result = "{";
    for (int i = 0; i < patientPriority.size(); i++) {
        result += integerToString(patientPriority[i]) + ": " + patientNames[i] + ",";
    }
    result += "}";
    return result;
}

