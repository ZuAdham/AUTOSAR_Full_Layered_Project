# 🚗 AUTOSAR-Based Project (Port, DIO, GPT Drivers)  

## 📌 Overview  
Welcome to the **AUTOSAR-based project** featuring **Port, DIO, and GPT drivers**!  
This implementation adheres to **AUTOSAR standard version 4.0.2**, providing functionality for:  
- Configuring and controlling port pins  
- Managing digital input/output  
- Facilitating timers within the AUTOSAR framework  

A **simple application** is included to demonstrate these drivers, running on a **lightweight OS**.  
Its core functionality revolves around activating tasks at predefined time intervals.  

---

## 📂 Contents  

### 🔹 AUTOSAR Port Driver  
Seamless configuration and control of microcontroller port pins, compliant with AUTOSAR 4.0.2.  

### 🔹 AUTOSAR DIO Driver  
Implements Digital I/O for efficient handling of input/output pins, enabling tasks to interact with external devices.  

### 🔹 AUTOSAR GPT Driver  
Provides timer configuration and management, serving as the foundation for time-based operations.  

### 🔹 Simple Application  
A minimal app showcasing integration of Port, DIO, and GPT drivers, activating tasks at set intervals.  

### 🔹 Simple OS  
A lightweight operating system handling task scheduling and time management for embedded projects.  

---

## ⚙️ Setup  

### Hardware Requirements  
- A microcontroller platform supporting AUTOSAR (e.g., Tiva-C series)  
- Basic peripherals (GPIOs, timers)  

### Software Dependencies  
- **Code Composer Studio (CCS)** for compilation and debugging  

### Configuration  
- Adjust **pin mappings, timer configs, and task schedules** to match your hardware  
- Update AUTOSAR configuration files accordingly  

### Build & Debug  
- Use CCS to compile and debug on target hardware  
- Utilize breakpoints and debug tools for troubleshooting  

### Flash  
- Flash the binary to the target microcontroller after successful build  

### Execute  
- Run the application on hardware and validate its functionality  

---

## 📖 AUTOSAR Documentation  
For more details on **AUTOSAR standard version 4.0.2**, visit the official [AUTOSAR website](https://www.autosar.org).  
Explore the **Classic Platform** for in-depth understanding of automotive software architecture.  

---

## 🚀 Usage  

- **Port Driver** → Configure/control port pins (input, output, alt functions)  
- **DIO Driver** → Manage digital inputs/outputs for external interaction  
- **GPT Driver** → Handle timers for task scheduling and time-based events  
- **Application Logic** → Explore example integration of drivers into real tasks  
- **OS Integration** → Lightweight OS coordinates task execution at intervals  

---

## 🔮 Future Enhancements  
- Extend **GPT driver** to support more Tiva-C timers  
- Improve scalability and flexibility for advanced time-based operations  
- Potential integration with higher-level AUTOSAR modules  

---

👨‍💻 **Author**: Adham  
