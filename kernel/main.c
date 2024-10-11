void main() {
	*((int*)0xb8000)='A';
	*((int*)0xb8001)=0x07;
}
