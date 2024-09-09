# This is the directory for my C++ writing and reading from disk program

## Functionality
The objective of these wrapper classes is to read and write files to disk

## Future Consideration: Multithreaded
- Add the ability to write to multiple files concurrently

### Implementation For Multithreaded
1. Choose a concurrency design
  - The dispatcher class holds both a reader and a writer (we spawn multiple dispatchers)
  - The dispatcher class will dynamically create readers and writers based on needs  
