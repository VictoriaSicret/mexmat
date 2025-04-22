class assistant:

    def __init__(self, name = "Jarvis"):
        self.__name = name

    def __del__(self):
        pass

    def Help(self):
        print(f"How {self.__name} can help you...\n{self.__name} is just programm.")

    @property
    def name(self):
        return self.__name
    @name.setter
    def name(self, name):
        self.__name = name


if (__name__ == "__main__"):
    main()


def main():
    helper = assistant("Bob")
    assist = assistant()
    helper.Help()

    while (True):
        print(assist.name)
        buff = input()
        if (buff == "-1"):
            break
        assist.name = buff

'''
def decor(function):
    def tmp(*args):
        print("my decor")
        print(function(args[0])(args[1]))
        print("my_decor")
    return tmp


@decor
def pow(k): return lambda p: k**p

pow(2, 3)

def cub (k): return k**3


name = input("Enter name: ")
password = input("Enter password: ")
print(password == "1234")
if (name == "Leon"):
    print("Hello, master!")
    print(f"I found square from {-1}\nIt equals {1j}\nHowever {-1} is {type(-1.)}, but {1j} is {type(1j)}")
else:
    print("Hello,", name)

for i in range(10): print(f"{i} in cube equals {cub(i)}")
'''
