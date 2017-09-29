// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "LinkedListPatientQueue.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    // TODO: write this constructor
    this->head = nullptr;
    this->size = 0;
}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    releaseNode();
}

void LinkedListPatientQueue::clear() {
    // TODO: write this function
    releaseNode();
    size = 0;
}

string LinkedListPatientQueue::frontName() {
    // TODO: write this function
    return head->name;
}

int LinkedListPatientQueue::frontPriority() {
    // TODO: write this function
    return head->priority;
}

bool LinkedListPatientQueue::isEmpty() {
    // TODO: write this function
    return size == 0;
}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
    PatientNode *current = head;
    PatientNode *patient = new PatientNode(name, priority);
    size++;

    // when the queue is empty
    if (head == nullptr) {
        head = patient;
    } else if (head->priority > priority) {
        patient->next = head;
        head = patient;
    } else {
        // when new node is in the middle
        while (current->next != nullptr && priority >= current->next->priority) {
            current = current->next;
        }

        patient->next = current->next;
        current->next = patient;
    }
}

string LinkedListPatientQueue::processPatient() {
    // TODO: write this function
    if (isEmpty())
        throw std::length_error("No patient");

    size--;
    PatientNode *current = head;
    head = current->next;
    string name = current->name;
    delete current;
    return name;
}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
    PatientNode *current = head;
    while (current != nullptr) {
        if (current->name == name) {
            current->priority = newPriority;
            // not reorder the node here
        }
    }

    // no patient found
    throw std::invalid_argument("No patient found");
}

string LinkedListPatientQueue::toString() {
    // TODO: write this function
    string result = "{";
    PatientNode *current = head;

    while (current != nullptr) {
        result += current->toString() + ";";
        current = current->next;
    }
    result += "}";
    return result; // this is only here so it will compile
}

void LinkedListPatientQueue::releaseNode() {
    PatientNode *current = head;
    while (head != nullptr) {
        head = head->next;
        delete current;
        current = head;
    }
}
