#include <iostream>
#include <filesystem>     // File && Directory Operations
#include <fstream>        // File Writting

class DumpFileHandler {

    std::string dumpFolder = "./Dump Folder";

    private:

        std::string generateTimestamp() {

            // System Time
            auto now = std::chrono::system_clock::now();
            auto time = std::chrono::system_clock::to_time_t(now);
            
            // Create string stream for timestamp
            std::stringstream ss;
            ss << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S_");
            
            // Add milliseconds
            auto duration = now.time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration) % 1000;
            ss << std::setfill('0') << std::setw(3) << millis.count() << ".dump";
            
            return ss.str();
        }
    
    public:

        void dumpFileReport() {

            // Creates Dump Folder
            if (!std::filesystem::exists(dumpFolder)) {
                std::filesystem::create_directories(dumpFolder);
            }
        
            // Generates File with TimeStamp as name
            std::string filename = dumpFolder + "/" + generateTimestamp();
            std::ofstream dumpFile(filename);
        
            // Write memory information
            dumpFile << "Memory Dump\n";

            /*
            dumpFile << "Total Memory Size: " << totalMemorySize << " bytes\n";
            dumpFile << "Allocated Blocks: " << allocatedBlocks.size() << "\n\n";
        
            // Dump details of each memory block
            for (size_t i = 0; i < allocatedBlocks.size(); ++i) {
                MemoryBlock* block = allocatedBlocks[i];
                dumpFile << "Block " << i << ":\n";
                dumpFile << "  Type: " << block->type << "\n";
                dumpFile << "  Size: " << block->size << " bytes\n";
                dumpFile << "  Reference Count: " << block->refCount << "\n";
                
                // Hexadecimal memory content dump
                unsigned char* bytes = static_cast<unsigned char*>(block->data);
                dumpFile << "  Memory Content (Hex): ";
                for (size_t j = 0; j < block->size; ++j) {
                    dumpFile << std::hex << std::setw(2) << std::setfill('0') 
                            << static_cast<int>(bytes[j]) << " ";
                }
                dumpFile << "\n\n";
            }
            */

            dumpFile.close();
        } 
};