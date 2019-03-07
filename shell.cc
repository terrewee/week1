#include "shell.hh"

using std::cout;
using std::cin;
using std::string;

int main(){
    string input;


    // ToDo: Vervang onderstaande regel: Laad prompt uit bestand
    std::string thingy;
    int fd = syscall(SYS_open, "command.txt", O_RDONLY);                // <<<<<<<< SYSCALL ------------------------
    std::vector<char> buff;
    buff.resize(512);
    ssize_t hanzel = read(fd, buff.data(), 512);
    buff.resize(hanzel);
    thingy = string(buff.begin(), buff.end());
    string prompt = thingy;

    while(true)
        {cout << prompt;                   // Print het prompt
        getline(cin, input);         // Lees een regel
        if (input == "new_file") new_file();   // Kies de functie
        else if (input == "ls") list();        //   op basis van
        else if (input == "src") src();        //   de invoer
        else if (input == "find") find();
        else if (input == "python") python();
        else if (input == "exit") return 0;
        else if (input == "quit") return 0;
        else if (input == "error") return 1;

        if (cin.eof()) return 0; } }      // EOF is een exit

void new_file(){ // ToDo: Implementeer volgens specificatie.
    string null;
    cout << "ToDo: Implementeer hier new_file()" << std::endl;
    cout << "name of file (don't forget extenson): ";
    string name;
    cin >> name;
    getline(cin, null);
    cout << "content (end with <EOF>): ";
    string content;
    getline(cin, content);
    const char *nameF = name.c_str(); 
    int fd = creat(nameF, 0644);
    const void * contentV = content.c_str();
    if(write(fd, contentV, content.size()) < 0){
        cout << "error!";
        perror("could not write file!");
    }
    close(fd);

    }

void list() // ToDo: Implementeer volgens specificatie.
    {cout << "ToDo: Implementeer hier list()" << std::endl; 
    int forkie = fork();
    if (forkie == 0){
        execl("/bin/ls", "ls", "-la", "/etc", (char *)0);
        }
        else{
            int exit_status;
            wait(&exit_status);
    }
}

void find(){ // ToDo: Implementeer volgens specificatie.
    string input;
    getline(std::cin, input);       

    pid_t pid;
    int mypipefd[2], status, ret;

    ret = pipe(mypipefd);

    if(ret == -1){
        perror("hij piped nie.");
        exit(1);
    }

    pid = fork();
    if(pid == 0) {
        char *args[] = {(char *) "find", (char *) "./", (char *)0};
        close(mypipefd[0]);
        dup2(mypipefd[1], STDOUT_FILENO);
        execv("/usr/bin/find", args);
    }

    pid = fork();
    if (pid == 0) {
        char *parm[] = {(char *) "grep", (char *) input.c_str(), (char *)0};
        close(mypipefd[1]);
        dup2(mypipefd[0], STDIN_FILENO);
        execv("/usr/bin/grep", parm);
    }

    close(mypipefd[0]);
    close(mypipefd[1]);

    waitpid(-1, &status, 0);
    waitpid(-1, &status, 0);
}

void python() // ToDo: Implementeer volgens specificatie.
    {cout << "ToDo: Implementeer hier python()" << std::endl; 
    int forkie = fork();
    if (forkie == 0){
        execl("/bin/python", "python", "/etc", (char *)0);
    }
    else{
        int exit_status;
        wait(&exit_status);
    }
}

void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
    {int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755);    // Gebruik de SYS_open call om een bestand te openen.
    char byte[1];                                               // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
    while(syscall(SYS_read, fd, byte, 1))                       // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
        cout << byte; }                                    //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.

    // 0644