#include "Field.h"
#include <thread>
#include <mutex>

Field::Field(const Grid& grid)
: nx(grid.get_nx()),
ny(grid.get_ny()),
values(nx * ny, 0.0)
{}

double& Field::operator()(std::size_t i, std::size_t j)
{
    return values[j * nx + i];
}

const double& Field::operator()(std::size_t i, std::size_t j) const
{
    return values[j * nx + i];
}

void Field::printField()
{
    for(size_t j = 0; j < ny; j++)
    {
        for(size_t i = 0; i< nx; i++)
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
}

void Field::setQuadraticField(const Grid& grid)
{
    for(int i=0; i<grid.get_nx(); i++)
    {
        for(int j=0; j<grid.get_ny(); j++)
        {
            (*this)(i,j) = pow(grid.get_x(i),2) + pow(grid.get_y(j),2);
        }
    }
}

double Field::calcFieldAverage() const
{
    double sum = 0.0;
    
    for(int i=0; i<nx; i++)
    {
        for(int j=0; j<ny; j++)
        {
            sum += (*this)(i,j);
        }
    }
    
    return sum / (nx * ny);
}

double Field::calcFieldAverageMultithread() const
{
    double sum = 0.0;
    std::vector<std::thread> threads;
    int nThreads = 4; // assume that 4 threads are used
    std::vector<double> partialSum(nThreads);
    
    const std::size_t jStart = 0;
    const std::size_t jEnd = get_ny();
    
    std::size_t rows = jEnd - jStart;
    std::size_t rowsPerThread = rows / nThreads;
    std::size_t remainder = rows % nThreads;
    
    std::size_t start = jStart;
    
    
    for(int t=0; t<nThreads; t++)
    {
        std::size_t end;
        if(t < remainder)
        {
            end = start + rowsPerThread + 1;
        }
        else
        {
            end = start + rowsPerThread;
        }
        
        //std::cout << "Thread " << t << ": [" << start << ", " << end << ")\n";
        
        threads.emplace_back(
                             [&, t, start, end]()
                             {
                                 double localSum = 0;
                                 for (std::size_t j = start; j < end; ++j)
                                 {
                                     for (std::size_t i = 0; i < nx; ++i)
                                     {
                                         localSum += (*this)(i,j);
                                     }
                                 }
                                 partialSum[t] = localSum;
                                 
                             }

                             );
        start = end;
        
    
    }
    
    for (auto& thread : threads)
    {
        thread.join();
    }
    
    for(double s: partialSum)
    {
        sum+=s;
    }
    
    
    return sum / (nx * ny);
}


/*
Mutex: protects a critical section so only one thread can execute it at a time.
std::lock_guard: manages locking/unlocking a mutex safely.
if mutex is locked and not unlocked (e.g. exception), then other threads can wait forever,
which causes deacdlock. The solution is lock_guard
when the execution leaves the scope, the destruction unlocks mutex
*/
double Field::calcFieldAverageMutex() const
{
    double sum = 0.0;
    std::mutex sumMutex;
    std::vector<std::thread> threads;
    int nThreads = 4; // assume that 4 threads are used
    
    const std::size_t jStart = 0;
    const std::size_t jEnd = get_ny();
    
    std::size_t rows = jEnd - jStart;
    std::size_t rowsPerThread = rows / nThreads;
    std::size_t remainder = rows % nThreads;
    
    std::size_t start = jStart;
    
    // auto ts0 = std::chrono::steady_clock::now();
    
    for(int t=0; t<nThreads; t++)
    {
        std::size_t end;
        if(t < remainder)
        {
            end = start + rowsPerThread + 1;
        }
        else
        {
            end = start + rowsPerThread;
        }
        
        //std::cout << "Thread " << t << ": [" << start << ", " << end << ")\n";
        
        threads.emplace_back(
                             [&, t, start, end]()
                             {
                                 
                                 
                                 double localSum = 0;
                                 for (std::size_t j = start; j < end; ++j)
                                 {
                                     for (std::size_t i = 0; i < nx; ++i)
                                     {
                                         localSum += (*this)(i,j);
                                     }
                                 }
                                 
                                 /*
                                  placing this before mutex increases the time by 100ms
                                  placing this after mutex increases the time by 400ms
                                  because that wait is executed 4 times
                                  std::this_thread::sleep_for(std::chrono::milliseconds(100));
                                  */
                                 std::lock_guard<std::mutex> lock(sumMutex);
                                 
                                 sum += localSum;
                                 
                             }
                             );

        start = end;
    }
    
    
    for (auto& thread : threads)
    {
        thread.join(); // block here until the worker has finished executing
    }
    
    /*
    auto ts1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> serialElapsed = ts1 - ts0;
    std::cout << "Time taken: " << serialElapsed.count() << "\n";
     */
    
    return sum / (nx * ny);

}





// SAVING FIELDS
void Field::saveCSV(const std::string& filename) const
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + filename);
    }

    for (std::size_t j = 0; j < ny; ++j)
    {
        for (std::size_t i = 0; i < nx; ++i)
        {
            file << (*this)(i, j);

            if (i < nx - 1)
            {
                file << ",";
            }
        }

        file << '\n';
    }
}
    
void writeVTK(
    const Field& field,
    const Grid& grid,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open VTK file");
    }

    const std::size_t nx = grid.get_nx();
    const std::size_t ny = grid.get_ny();

    file << "# vtk DataFile Version 3.0\n";
    file << "Diffusion solution\n";
    file << "ASCII\n";
    file << "DATASET STRUCTURED_POINTS\n";

    file << "DIMENSIONS "
         << nx << " "
         << ny << " "
         << 1 << "\n";

    file << "ORIGIN "
         << grid.get_start_x() << " "
         << grid.get_start_y() << " "
         << 0.0 << "\n";

    file << "SPACING "
         << grid.get_dx() << " "
         << grid.get_dy() << " "
         << 1.0 << "\n";

    file << "POINT_DATA " << nx * ny << "\n";
    file << "SCALARS solution double 1\n";
    file << "LOOKUP_TABLE default\n";

    for (std::size_t j = 0; j < ny; ++j)
    {
        for (std::size_t i = 0; i < nx; ++i)
        {
            file << field(i, j) << "\n";
        }
    }
    
    //std::cout << "Written to VTK! \n";
}
