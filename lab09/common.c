#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "common.h"

long long int sum(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
	__m128i mask = _mm_set1_epi32(0);
	__m128i temp = _mm_set1_epi32(0);

	unsigned int sum_temp[4];
	
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* YOUR CODE GOES HERE */
		// Initialize a sum vector
		__m128i sum = _mm_set1_epi32(0);

		// Iterate to get the result
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			// Load the array
			temp = _mm_loadu_si128((__m128i *)(vals+i));

			// Compare the vector
			mask = _mm_comgt_epi32(temp, _127);

			// Bitwise-and to get the component to sum
			temp = _mm_and_si128(temp, mask);

			// Sum temp to sum-vector
			sum = _mm_add_epi32(sum, temp);

		}
		/* You'll need a tail case. */
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}

		_mm_storeu_si128((__m128i_u *) sum_temp, sum);
		
		result += sum_temp[0] + sum_temp[1] + sum_temp[2] + sum_temp[3];
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;

	__m128i mask = _mm_set1_epi32(0);
	__m128i temp = _mm_set1_epi32(0);

	unsigned int sum_temp[4];

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* COPY AND PASTE YOUR sum_simd() HERE */
		/* MODIFY IT BY UNROLLING IT */
		// Initialize a sum vector
		__m128i sum = _mm_set1_epi32(0);

		// Iterate to get the result
		for(unsigned int i = 0; i < NUM_ELEMS / 16 * 16; i += 16) {
			// Load the array
			temp = _mm_loadu_si128((__m128i *)(vals+i));

			// Compare the vector
			mask = _mm_comgt_epi32(temp, _127);

			// Bitwise-and to get the component to sum
			temp = _mm_and_si128(temp, mask);

			// Sum temp to sum-vector
			sum = _mm_add_epi32(sum, temp);

			// Load the array
			temp = _mm_loadu_si128((__m128i *)(vals+i+4));

			// Compare the vector
			mask = _mm_comgt_epi32(temp, _127);

			// Bitwise-and to get the component to sum
			temp = _mm_and_si128(temp, mask);

			// Sum temp to sum-vector
			sum = _mm_add_epi32(sum, temp);

			// Load the array
			temp = _mm_loadu_si128((__m128i *)(vals+i+8));

			// Compare the vector
			mask = _mm_comgt_epi32(temp, _127);

			// Bitwise-and to get the component to sum
			temp = _mm_and_si128(temp, mask);

			// Sum temp to sum-vector
			sum = _mm_add_epi32(sum, temp);

			// Load the array
			temp = _mm_loadu_si128((__m128i *)(vals+i+12));

			// Compare the vector
			mask = _mm_comgt_epi32(temp, _127);

			// Bitwise-and to get the component to sum
			temp = _mm_and_si128(temp, mask);

			// Sum temp to sum-vector
			sum = _mm_add_epi32(sum, temp);

		}
		/* You'll need a tail case. */
		for(unsigned int i = NUM_ELEMS / 16 * 16; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				result += vals[i];
			}
		}

		_mm_storeu_si128((__m128i_u *) sum_temp, sum);
		
		result += sum_temp[0] + sum_temp[1] + sum_temp[2] + sum_temp[3];
	
		/* You'll need 1 or maybe 2 tail cases here. */

	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}