#pragma

#include <string_view>

#include <raylib.h>


namespace zv
{
  class FileUtils
  {
  public:
    static bool file_exists(const char* file_path)
    {
      return FileExists(file_path);
    }

    static std::string_view get_application_directory()
    {
      return GetApplicationDirectory();
    }

  /*
    // Files management functions
    unsigned char *LoadFileData(const char *fileName, int *dataSize); // Load file data as byte array (read)
    void UnloadFileData(unsigned char *data);                   // Unload file data allocated by LoadFileData()
    bool SaveFileData(const char *fileName, void *data, int dataSize); // Save data to file from byte array (write), returns true on success
    bool ExportDataAsCode(const unsigned char *data, int dataSize, const char *fileName); // Export data to code (.h), returns true on success
    char *LoadFileText(const char *fileName);                   // Load text data from file (read), returns a '\0' terminated string
    void UnloadFileText(char *text);                            // Unload file text data allocated by LoadFileText()
    bool SaveFileText(const char *fileName, char *text);        // Save text data to file (write), string must be '\0' terminated, returns true on success
    //------------------------------------------------------------------

    // File system functions
    bool FileExists(const char *fileName);                      // Check if file exists
    bool DirectoryExists(const char *dirPath);                  // Check if a directory path exists
    bool IsFileExtension(const char *fileName, const char *ext); // Check file extension (including point: .png, .wav)
    int GetFileLength(const char *fileName);                    // Get file length in bytes (NOTE: GetFileSize() conflicts with windows.h)
    const char *GetFileExtension(const char *fileName);         // Get pointer to extension for a filename string (includes dot: '.png')
    const char *GetFileName(const char *filePath);              // Get pointer to filename for a path string
    const char *GetFileNameWithoutExt(const char *filePath);    // Get filename string without extension (uses static string)
    const char *GetDirectoryPath(const char *filePath);         // Get full path for a given fileName with path (uses static string)
    const char *GetPrevDirectoryPath(const char *dirPath);      // Get previous directory path for a given path (uses static string)
    const char *GetWorkingDirectory(void);                      // Get current working directory (uses static string)
    const char *GetApplicationDirectory(void);                  // Get the directory of the running application (uses static string)
    bool ChangeDirectory(const char *dir);                      // Change working directory, return true on success
    bool IsPathFile(const char *path);                          // Check if a given path is a file or a directory
    FilePathList LoadDirectoryFiles(const char *dirPath);       // Load directory filepaths
    FilePathList LoadDirectoryFilesEx(const char *basePath, const char *filter, bool scanSubdirs); // Load directory filepaths with extension filtering and recursive directory scan
    void UnloadDirectoryFiles(FilePathList files);              // Unload filepaths
    bool IsFileDropped(void);                                   // Check if a file has been dropped into window
    FilePathList LoadDroppedFiles(void);                        // Load dropped filepaths
    void UnloadDroppedFiles(FilePathList files);                // Unload dropped filepaths
    long GetFileModTime(const char *fileName);                  // Get file modification time (last write time)
*/
  };
}
