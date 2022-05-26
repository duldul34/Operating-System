#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd1, fd2, i, n_write, n_read = 0;
    int msg;
    int toSend;

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
        if ((n_read = read(fd1, &msg, sizeof(msg))) == -1)
        {
            printf("Read Error\n");
            return -1;
        }

        toSend = msg + 10;
        if ((n_write = write(fd2, &toSend, sizeof(i))) == -1)
        {
            printf("Write Error\n");
            return -1;
        }

        printf("Consumer Received: %d, Consumer Sent: %d\n", msg, toSend);
        sleep(2);
    }

    close(fd1);
    close(fd2);
    return 0;
}