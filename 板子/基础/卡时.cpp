
const double limit=0.95;
const int maxc=limit*CLOCKS_PER_SEC;
int step=0;

while (1) {
	step++;
	if (step%1000 == 0 and clock() > maxc) break;
}
