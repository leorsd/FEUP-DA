# Route Planner Project

This project is a **Pallet Optimization Tool** developed for the **DA 2025 - 2nd Project**.  
It applies various algorithms to determine the most profitable combination of pallets that can be loaded into a truck, while respecting capacity constraints.  
The goal is to maximize profit without exceeding the truck's weight or space limits.

It was developed by:

- Afonso Miguel Almeida Pereira, up202305652@up.pt
- Leandro Filipe Pais Resende, up202306343@up.pt
- Mo'men Sami Ahmad Alhammadin, up202411533@up.pt


## Algorithms Implemented

- **Brute Force**
- **Backtracking**
- **Greedy**
- **Dynamic Programming**
- **Integer Linear Programming**

## **Documentation**
To better understand the code, documentation has been provided. It was generated using **Doxygen**. To access it, navigate to the **documentation** folder and open the `index.html` file in your preferred browser.

## Building and Running the Project

This project uses **CMake** to generate a Makefile, which is then used to compile the source code. Follow the steps below to build and execute the project successfully.

### **1. Ensure You Have a Build Directory**
Before running CMake, navigate to the **SourceCode** folder. If a **build** folder does not exist inside it, create one:

```sh
mkdir -p build
```

### **2. Navigate to the Build Directory**
Move into the **build** directory:

```sh
cd build
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