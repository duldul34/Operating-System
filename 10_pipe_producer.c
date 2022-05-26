#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd1, fd2, i, n_write, n_read = 0;
    int msg;

    mkfifo("/tmp/my_pipe1", 0644);
    mkfifo("/tmp/my_pipe2", 0644);

    if ((fd1 = open("/tmp/my_pipe1", O_RDONLY, 0644)) == -1)
    {
        printf("Pipe Open Error\n");
        return -1;
    }

    if ((fd2 = open("/tmp/my_pipe1", O_RDONLY, 0644)) == -1)
    {
        printf("Pipe Open Error\n");
        return -1;
    }

    for (i = 0; i < 10; i++)
    {
        if ((n_write = write(fd1, &i, sizeof(i))) == -1)
        {
            printf("Write Error\n");
            return -1;
        }

        if ((n_read = read(fd2, &msg, sizeof(msg))) == -1)
        {
            printf("Read Error\n");
            return -1;
        }

        printf("Producer Sent: %d, Consumer Received: %d\n", i, msg);
        sleep(1);
    }

    close(fd1);
    close(fd2);
    return 0;
}