const { execSync } = require('child_process')

while (true) {
	let i = 0
	let out
	do {
		out = execSync('./philo 5 800 200 200 7 | grep eating | wc -l')
		i++
		process.stdout.write('.')
	} while (out.toString().trim() == '35')
	process.stdout.write(`\n err ${i}\n`)
}


// while (true) {
// 	execSync('./philo 4 410 200 200')
// 	process.stdout.write(`\n err`)
// }
