
# restore commands generated from translator
cmds = []

# explain a proposition which is splited by ' '
# return a list containing numbers and operators
# the numbers are ids from 0 to n - 1
def translator(prop):
    elements = prop.split(' ')

    for i in range(len(elements)):
        if elements[i].isdigit():
            elements[i] = int(elements[i])

    print("Generated {}".format(elements))
    return elements


# the cmd is a list of numbers and operators
# cond denotes everyone's identity, in binary
# emulator will replace the number with 0 or 1
# then exec() it
def emulator(cmd, cond):
    print(cmd)

    for i in range(len(cmd)):
        if isinstance(cmd[i], int):
            cmd[i] = str(1 & (cond >> cmd[i]))

    c = ' '.join(cmd)
    res = eval(c)
    print("Executing command " + c +", the result is", res)
    return res 


def main():
    n = int(input("Total number of people："))
    w = 2 << n - 1

    for i in range(n):
        cmds.append(translator(input("The person with ID {} said：".format(i))))

    print('cmds:', cmds, '\n')
    cnt_ok = 0

    for cond in range(w):
        cond_ok = True
        print("Situation " + bin(cond)[2:].zfill(n))

        for i in range(n):
            cmd = cmds[i]
            if ((cond >> i) & 1) ^ emulator(cmd, cond):
                cond_ok = False
                break

        print("cmds", cmds)

        if cond_ok:
            print("Situation {} is ok!".format(bin(cond)[2:]))
            cnt_ok += 1


    if cnt_ok == 1 or cnt_ok == 0:
        noun = ''
        verb = 's'
    else:
        noun = 's'
        verb = ''

    print("{} situation{} meet{} the question set".format(cnt_ok, noun, verb))


if __name__ == "__main__":
    main()      