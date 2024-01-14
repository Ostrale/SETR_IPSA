import subprocess

def progress_bar(progress, total):
    percent = 100 *(progress/ float(total))
    bar = '▮' * int(percent) + '-' * (100 - int(percent))
    print(f"\r|{bar}|{percent:.2f}%",end="\r")
    if progress == total:
        print("▮")

# Nombre d'itérations
iterations = 1000

# Commandes à exécuter
commands = ["bash -c 'time ./t 1'", "bash -c 'time ./t 2'", "bash -c 'time ./t 3'", "bash -c 'time ./t 4'"]
max_time = [0.0, 0.0, 0.0, 0.0] # in milliseconds



# Boucle pour exécuter les commandes spécifiées
for command in commands:
    for i in range(iterations):
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, shell=True)
        time_not_formatted = result.stderr
        # on extrait le texte qui se trouve entre "." et "s"
        time = float(time_not_formatted[time_not_formatted.find(".") + 1:time_not_formatted.find("s")])
        if time > max_time[commands.index(command)]:
            max_time[commands.index(command)] = time
        progress_bar(i+1,iterations)
    # print WCET
    print("WCET for " + command + " : " + str(max_time[commands.index(command)]) + " ms")

for i in range(len(max_time)):
    print("WCET for task " + str(i) + " : " + str(max_time[i]) + " ms")