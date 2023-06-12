import crc from "./crc";
import { Server } from "net";
import { ACCEPTABLE_HASH, PORT } from "./Constants";
import { promisify } from "util";
import { writeFile } from "fs/promises";
import * as cp from "child_process";
import * as tmp from "tmp";
import { join } from "path";

const exec = promisify(cp.exec);
const nc = new Server();
let i = 0;

nc.on("connection", sock => {
	let child: cp.ChildProcess = null;
	let child_open = false;
	sock.on("data", async data=>{
		if (sock.readyState === "open") {
			if (child !== null) {
				if (child_open) {
					child.stdin.write(data);
				} else {
					sock.end();
				}
				return;
			}

			let hash: string = crc(data);
			console.log(hash);
			let temp = tmp.dirSync();
			if (hash == ACCEPTABLE_HASH) {
				let infile = join(temp.name, "in.c");
				let outfile = join(temp.name, "out");
				await writeFile(infile, data, {encoding: null});
				try {
					await exec(`gcc ${infile} -o ${outfile} -lm`);
				} catch(e) {
                    console.log(e);
					sock.write("ERROR: Compilation failed!");
					sock.end();
					return;
				}
				child = cp.spawn(outfile);
				child_open = true;
				console.log("spawning child process");
				child.stdout.on("data", d=>{
					console.log("stdout", d);
					if (sock.readyState == "open") {
						sock.write(d);
					}
				})
				const err = ()=>{console.log("Child Exited");child_open = false;};
				child.on('close', err);
				child.on('error', err);
			} else {
				sock.write(`ERROR: Refusing to run file, invalid checksum (${hash})!\n`);
				sock.end();
			}
		}
	});
	sock.on("close", s=>{
		if (child) {
			child.kill();
		}
	});
});

nc.listen(PORT, "0.0.0.0");