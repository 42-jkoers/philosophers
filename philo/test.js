const { execSync } = require('child_process')

let i = 0
let out
do {
	out = execSync('./philo 5 800 200 200 7 | grep eating | wc -l')
	i++
} while (out.toString().trim() == '35')
console.log('err', i)
