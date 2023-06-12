import { parentPort } from "worker_threads";
import crc from "./crc";
import { ACCEPTABLE_HASH } from "./Constants";
import * as fs from "fs/promises";
import { randomBytes } from "crypto";

async function solve() {
	let malicious = (await fs.readFile("prog/collide.c")).toString();
	let file = "";
	let hash = "";
	/*let codex = Array(8).fill(null).map(x=>{
		return {
			"0": 0,
			"1": 0,
			"2": 0,
			"3": 0,
			"4": 0,
			"5": 0,
			"6": 0,
			"7": 0,
			"8": 0,
			"9": 0,
			"a": 0,
			"b": 0,
			"c": 0,
			"d": 0,
			"e": 0,
			"f": 0
		} as {[e:string]:number};
	});*/
	let ctr = 0;
	while (hash !== ACCEPTABLE_HASH) {
		file = malicious+"\n//"+randomBytes(128).toString("hex");
		//hash = crc(file);
		/*for (let i = 0; i < hash.length; i++) {
			codex[i][hash[i]]++;
		}*/
		ctr++;
		if (ctr % 1000000 == 0) {
			parentPort.postMessage({"update": 1000000});
			//console.log(codex);
			//console.log(codex.map(item=>getStandardDeviation(Object.values(item))))
			//return;
		}
	}
	parentPort.postMessage({found: hash});
	await fs.writeFile("accepted.c", file);
}
solve();