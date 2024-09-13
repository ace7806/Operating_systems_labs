int bestfit(int low, int startscan, int pages, int memflags, int *len)
{
	
	int run_length = 0, i;
	int freerange_start = startscan;
	int holeStart =0, bettetfit=startscan-low+1,betterStart=0,betterEnd=0,better_freerange_start=0;

	printf("---BEST FIT START---\n");
	printf("Initial position of the search: %d\n",startscan);
	printf("Limit position of the search: %d\n",low);
	printf("Number of pages needed: %d\n",pages);

	for(i = low; i <= startscan; i++) {
		if(!page_isfree(i)) {
			if(holeStart>0){
				if (bettetfit>i-holeStart)
				{
					printf("-BETTER FIT FOUND-\n");
					betterStart=holeStart;
					betterEnd=i-1;
					bettetfit=i-holeStart;
					better_freerange_start=freerange_start;
				}
				printf("Hole Start: %d\n",holeStart);
				printf("Hole End: %d\n",i-1);
				printf("Hole Size: %d\n",i-holeStart);
				holeStart=0;
			}
			int pi;
			int chunk = i/BITCHUNK_BITS, moved = 0;
			run_length = 0;
			pi = i;
			while(chunk > 0 &&
			   !MAP_CHUNK(free_pages_bitmap, chunk*BITCHUNK_BITS)) {
				chunk--;
				moved = 1;
			}
			if(moved) { i = chunk * BITCHUNK_BITS + BITCHUNK_BITS; }
			continue;
		}
		if(!run_length) { freerange_start = i; run_length = 1;}
		else { freerange_start--; run_length++;}
		assert(run_length <= pages);
		if(run_length == pages) {
			printf("--HOLE CANDIDATE FOUND--\n");
			holeStart =i-pages+1;
			*len = run_length;
		}
	}
	printf("---BEST FIT END---\n");
	if (betterStart!=betterEnd)
	{
		printf("-BEST FIT FOUND-\n");
		printf("Hole Start: %d\n",betterStart);
		printf("Hole End: %d\n",betterEnd);
		printf("Hole Size: %d\n",bettetfit);

		return better_freerange_start;
	}
	
	return NO_MEM;
}