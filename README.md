# Freelance Marketplace Manager

A lightweight, console-based simulation of a freelance platform developed in standard C++. The system models real-world interactions between clients and freelancers using core Object-Oriented Programming (OOP) concepts, featuring data persistence via local file streams.

## 🚀 Features

* **Role-Based User Architecture:** Distinct functionalities for **Clients** (post projects) and **Freelancers** (view marketplace, apply for open listings).
* **Data Persistence:** Automatic tracking and saving of active project states to a comma-separated local `.txt` file upon system exit.
* **Polymorphic Runtime Engine:** Dynamic resolution of user profile rendering dependent on real-time authentication contexts.
* **Memory Optimization:** Active tracking and clean deallocation of heap-allocated resources to eliminate runtime memory leaks.

## 🛠️ Core OOP Architecture

The system maps a real-world scenario directly to strict structural paradigms:

* **Inheritance Hierarchy:** Implements a unified type system branching from a generic `User` base class into specialized `Client` and `Freelancer` subclasses. Project tracking similarly relies on a hierarchical tree where `ClientProject` inherits from a core `BaseProject` structural layout.
* **Encapsulation:** Protects sensitive fields (e.g., private financial rates, structural records) behind rigid access specifiers, mediating mutation strictly through public interfaces and accessor methods.
* **Runtime Polymorphism:** Leverages standard virtual functions (`displayInfo()`, `displayProjectDetails()`) linked to base pointer collections (`vector<User*>`) to execute dynamic binding.

## 💻 System Requirements

* **Compiler:** Any standard GCC-compatible C++ compiler supporting standard dynamic containers and stream libraries (e.g., `g++`).
* **OS:** Cross-platform compatibility across Windows and Linux environments.

## 📂 File Output Layout

Data states persist locally using a simplified, comma-separated formatting structure:
```text
P101,Web Prototype,C1,F1,0
P102,Circuit Design,C1,None,0
P103,Mobile App Design,C1,None,0
