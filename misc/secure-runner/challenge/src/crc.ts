import * as c from "buffer-crc32";

export default function crc(str: Buffer): string {
	return c(str).toString("hex");
}