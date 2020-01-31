import sys

EATING = 1
SLEEPING = 2
THINKING = 3
DEAD = 4
WAITING = 5
filename = "log.log"


class Philo():
    def __init__(self, num, tot):
        self.state = 0
        self.num = num
        self.f_left = num
        self.f_right = (num - 1) % tot
        self.p_left = (num + 1) % tot
        self.p_right = (num - 1) % tot
    
        if self.f_left == tot:
            self.f_left = 0

        if self.p_left == 0:
            self.p_left = tot
        if self.p_right == 0:
            self.p_right = tot
        
        self.time_to_die = None
    def __str__(self):
        return "num : {} || f_left : {} || f_right : {} || p_left : {} || p_right : {}".format(self.num, self.f_left, self.f_right, self.p_left, self.p_right)



class Checker():
    def __init__(self, filename, n_philo, time_to_die, time_to_eat, time_to_sleep, nb_eat):
        self.philos = {}
        for i in range(1, int(n_philo) + 1):
            self.philos[str(i)] = Philo(i, int(n_philo))
        self.forks = {}
        for i in range(0, int(n_philo)):
            self.forks[i] = "free"

        self.time_to_die = int(time_to_die)
        self.time_to_eat = int(time_to_eat)
        self.time_to_sleep = int(time_to_sleep)
        self.nb_eat = int(nb_eat)
        f = open(filename, "r")
        self.lines = f.readlines()
        f.close()
        self.nb_line = 1


    def __str__(self):
        ret = "philos : \n"
        for key, val in self.philos.items():
            ret += "\t{} : {}\n".format(key, val.__str__())
        ret += "forks : {}".format(self.forks)
        return ret
    def check(self):
        try:
            for line in self.lines:
                tab = line.split()
                self.update_philos(tab)
                self.nb_line += 1
        except Exception as e:
            self.problem = e.__str__()
            return False
        return True
    
    def take_fork(self, philo, timestamp):
        if self.forks[philo.f_left] != "free":
            raise Exception ("philo {} tried to take fork {} already_used by {}".format(philo.num, philo.f_left, self.forks[philo.f_left]))
        self.forks[philo.f_left] = philo.num

        if self.forks[philo.f_right] != "free":
            raise Exception ("philo {} tried to take fork {} already_used by {}".format(philo.num, philo.f_right, self.forks[philo.f_right]))
        self.forks[philo.f_right] = philo.num

        if philo.time_to_die and philo.time_to_die < int(timestamp):
            raise Exception ("philo {} should have been dead".format(philo.num))

    def die(self, philo, timestamp):
        if philo.time_todie and philo.time_to_die + 10 < int(timestamp):
            raise Exception ("philo {} should have been dead".format(philo.num))


    def eat(self, philo, timestamp):
        philo.time_to_die = int(timestamp) + self.time_to_die
        if philo.time_to_die and philo.time_to_die < int(timestamp):
            raise Exception ("philo {} should have been dead".format(philo.num))

    def sleep(self, philo, timestamp):
        if philo.time_to_die and philo.time_to_die < int(timestamp):
            raise Exception ("philo {} should have been dead".format(philo.num))
        self.forks[philo.f_left] = "free"
        self.forks[philo.f_right] = "free"

    def think(self, philo, timestamp):
        if philo.time_to_die and philo.time_to_die < int(timestamp):
            raise Exception ("philo {} should have been dead".format(philo.num))

    def update_philos(self, tab):
        philo = self.philos[tab[1]]
        if tab[2] == "has":
            self.take_fork(philo, tab[0])
        elif tab[2] == "died":
            self.die(philo, tab[0])
        elif tab[2] == "is" and tab[3] == "eating":
            self.eat(philo, tab[0])
        elif tab[2] == "is" and tab[3] == "sleeping":
            self.sleep(philo, tab[0])
        elif tab[2] == "is" and tab[3] == "thinking":
            self.think(philo, tab[0])
        else:
            raise Exception("wrong line format")



if len(sys.argv) < 5 or len(sys.argv) > 6:
    print("5 or 6 args")
    exit()

if len(sys.argv) == 5:
    sys.argv.append("-1")
checker = Checker(filename, sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4], sys.argv[5])
print(checker)
if checker.check() == True:
    print("Trace ok")
else:
    print("Trace wrong: \n\tline : {} \n\tproblem : {}".format(checker.nb_line, checker.problem))

