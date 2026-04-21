import sys


def module(): 
    return "is module"
async def sysf(cmd):
    result = sys.exec(cmd) == 0
    return result
if __name__ == "__main__":
    module()
    sys.arg("ls")

