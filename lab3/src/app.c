#include "defstrerr.h"
#include "io.h"
#include "do.h"
#include "funcwithmatrix.h"

const func_var sizze[5] = {10, 50, 100, 500, 1000};
const char name_file[10][100] = {"./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x1.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt",
                                 "./data/10x10.txt"};


int main ()
{
    setbuf(stdout, NULL);
    print_hello();

    int num_command = -1;

    func_var multi_res = 0;

    while (num_command != 0)
    {
        printf_input();
        if (check_number(&num_command, 0, 17) != OK)
        {
            printf("%s%s",
                   "ERROR!!!\n",
                   "Invalid command entered, please re-enter!!!\n");

            print_hello();
        }
        else
        {
            func_var code_err;
            code_err = do_action(num_command, &multi_res);

            if (code_err)
            {
                return code_err;
            }
        }
    }

    return OK;
}




