# Route Planner Project

This project is a **route planner program** developed for the **DA 2025 1st Project**. It calculates optimal routes based on given parameters and provides an efficient way to navigate between locations.

It was developed by:

- Afonso Miguel Almeida Pereira, up202305652@up.pt
- Leandro Filipe Pais Resende, up202306343@up.pt
- Mo'men Sami Ahmad Alhammadin, up202411533@up.pt

## **Documentation**
To better understand the code, a documentation has been provided. It was generated using **Doxygen**. To access it, navigate to the **documentation** folder and open the `index.html` file in your preferred browser.

## Building and Running the Project

This project uses **CMake** to generate a Makefile, which is then used to compile the source code. Follow the steps below to build and execute the project successfully.

### **1. Ensure You Have a Build Directory**
Before running CMake, navigate to the **SourceCode** folder. If a **Build** folder does not exist inside it, create one:

```sh
mkdir -p SourceCode/Build
```

### **2. Navigate to the Build Directory**
Move into the **Build** directory:

```sh
cd SourceCode/Build
```

### **3. Generate the Makefile**
Run the following command to generate the Makefile:

```sh
cmake ..
```

### **4. Compile the Code**
Use the generated Makefile to compile the project:

```sh
make
```

### **5. Run the Executable**
Once the compilation is complete, you can execute the project using:

```sh
./DA_Project
```

This will run the compiled application.