#include <mettaton/libneko.h>

int main()
{
    nekolib::save_nekos("test/test.req",
                        "https://api.thecatapi.com/v1/images/search");
}