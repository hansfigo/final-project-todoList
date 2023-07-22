#include <iostream>
#include <vector>
#include <string>
#include <sstream>
 
using namespace std;
 
class ToDoList
{
private:
    // Inisialisasi Array untuk menampung list Task
    vector<string> taskList;
 
public:
    // Method untuk menambahkan Task
    void addTask(string task)
    {
        taskList.push_back(task);
    }
 
    // Method untuk menampilkan task
    void showTask()
    {
        // Check jika task kosong atau tidak
        if (taskList.empty())
        {
            cout << "No List\n";
        }
        else
        {
            int i = 0;
            for (auto elem : taskList)
            {
                cout << i + 1 << "." << elem << endl;
                i++;
            }
        }
    }
    // Method untuk delete task
    void deleteTask(int index)
    {
        try
        {
            taskList.erase(taskList.begin() + index - 1);
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};
 
// Function untuk split string (cuman copas di internet)
void tokenize(const string &str, vector<std::string> &out)
{
    // Buat Stream dari String
    istringstream ss(str);
 
    std::string s;
 
    while (ss >> s)
    {
        out.push_back(s);
    }
}
 
// Function untuk show vector data, debug only !
void showVectorData(vector<std::string> &data)
{
    cout << "\nVector Data :" << endl;
    for (auto &elem : data)
    {
        cout << elem << endl;
    }
}
 
int main()
{
    // Inisialisasi object todo
    ToDoList todo;
 
    string input;
    bool running = true;
 
    vector<string> userInput;
    cout << "\nTODOLIST APP : \n\n";
    cout << "Command: \n\n";
    cout << "   Add Task : add <task>\n";
    cout << "   Delete Task : delete <taskNumber>\n";
    cout << "   Show Task : show\n";
    cout << "   Exit Program : exit\n\n";
 
    // Selama Status masih running, akan execute code dibawah ini
    while (running)
    {
        cout << "\n> ";
 
        // Terima Input User
        getline(cin, input);
 
        // Setelah itu kita split input user menjadi 2 bagian
        tokenize(input, userInput);
 
        // pada if else berikut, akan cek value dari input user bagian ke 2
        // ADD
        if (userInput.at(0) == "add")
        {
            // inisialisasi variable untuk menanpung input task yang lebih dari 1 kata
            string combinedTask;
 
            // Check jika input user yang displit memiliki lebih dari 1 bagian atau tidak
            if (userInput.size() > 1)
            {
                // Loop vector untuk handle
                int i = 0;
                for (auto &element : userInput)
                {
                    // skip bagian pertama dari input user (karena bagian pertama command)
                    if (i != 0)
                    {
                        // menambahkan value dari userInput index ke-i kedalam variable combined task
                        combinedTask += userInput.at(i);
 
                        // Jika User input tadi memiliki banyak bagian, kita tambah kan spasi untuk menghubungkan setiap bagiannya
                        if (i < userInput.size() - 1)
                        {
                            combinedTask += " ";
                        }
                    }
                    i++;
                }
 
                // panggil method addTask untuk menambakan task
                todo.addTask(combinedTask);
                cout << "Task Added\n";
            }
            // jika tidak berarti tidak memiliki task, alias hanya command
            else
            {
                cout << "Missing Argument : add <task>\n";
            }
        }
 
        // SHOW
        else if (userInput.at(0) == "show")
        {
            // memanggil method showTask untuk menampilkan list task
            todo.showTask();
        }
 
        // DELETE
        else if (userInput.at(0) == "delete")
        {
            // Check jika input user yang displit memiliki lebih dari 1 bagian atau tidak
            if (userInput.size() > 1)
            {
                try
                {
                    // convert input user bagian ke 2 dari string ke int
                    int index = stoi(userInput.at(1));
 
                    // Validasi task ke berapa yang mau di delete
                    if (index > 0 && index < userInput.size())
                    {
                        // Panggil method untuk delete task index ke
                        todo.deleteTask(index);
                        cout << "Task Deleted\n";
                    }
                    else
                    {
                        cout << "Invalid index: Angka List tidak sesuai\n";
                    }
                }
                // Menangkap Exepction jika user input nya string , harusnya int
                catch (const std::invalid_argument &e)
                {
                    cout << "Invalid argument, hanya bisa di isi ANGKA\n";
                }
            }
            else
            {
                cout << "Missing Argument : delete <taskNumber>\n";
            }
        }
 
        // EXIT
        else if (userInput.at(0) == "exit")
        {
            if (userInput.size() > 1)
            {
                cout << "Unexpected Argument\n";
            }
            else
            {
                break;
            }
        }
 
        // UNKNOWN
        else
        {
            cout << "Unknown command : " << userInput.at(0) << endl;
        }
        //Clear input user
        userInput.clear();
    }
    return 0;
}
 