#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/ucontext.h>
#include <pwd.h>

static void sig_handler(int my_sig, siginfo_t *sig_info, void *cont)
{
    //getting pid 
    pid_t getting_pid = sig_info->si_pid;
    //getting uid
    uid_t getting_uid = sig_info -> si_uid;
    struct passwd *pw = getpwuid(getting_uid);
    //user name path
    const char *send_user_name = pw -> pw_name;
    ucontext_t* ucontext = reinterpret_cast<ucontext_t*>(cont);
    
    std::cout << "Received a SIGUSR1 signal from process" << getting_pid << "executed by" << getting_uid << " " << send_user_name << std::endl;
    std::cout << "EIP: " << ucontext->uc_mcontext.gregs[REG_RIP]<< std::endl;
    std::cout << "EAX: " << ucontext->uc_mcontext.gregs[REG_RAX] << std::endl;
    std::cout << "EBX: " << ucontext->uc_mcontext.gregs[REG_RBX] << std::endl;

}

int main ()
{
    struct sigaction act;
    memset (&act, '\0', sizeof(act));

    //using sa_sigaction for our handler
    act.sa_sigaction = &sig_handler;
    
    //giving flag to tell sigaction() to use the sa_sigaction field
    act.sa_flags = SA_SIGINFO;
    
    //checking if is correct 
    if (sigaction(SIGUSR1, &act, NULL) < 0) {
      std::cerr << strerror(errno) << std::endl;
      exit(errno);
    }

    //getting the pid
    std::cout << "PID:" << getpid() << std::endl;
    
    while (true){
        sleep (10);
    }
    return 0;
}