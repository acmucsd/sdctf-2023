import { Worker } from "worker_threads";

async function start_threads() {
	const workers = Array(8).fill(0).map(x=>{
		return new Worker("./build/worker.js",{
			workerData: {
				thread_count: 8
			}
		});
	})
	let total = 0;
	workers.forEach(worker => {
		worker.on("message", msg=>{
			if (msg.update) {
				total += msg.update
				console.log(total);
			} else if (msg.found) {
				console.log(msg.file);
				workers.forEach(work=>work.terminate());
			}
		});
	});
}

start_threads();