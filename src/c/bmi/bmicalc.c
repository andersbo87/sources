/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
 * Copyright (C) 2015 Anders Bolt-Evensen
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name ``Anders Bolt-Evensen'' nor the name of any other
 *    contributor may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 * 
 * bmicalc IS PROVIDED BY ANDERS BOLT-EVENSEN ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL  OR ANY OTHER CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
int main()
{
	printf("Program for å kalkulere kroppsmasseindeks.\n");
	int bmi;
	float height, weight;
	printf("Skriv inn vekta di (i kilo): ");
	scanf("%f",&weight);
	printf("Skriv inn høyden din (i meter): ");
	scanf("%f", &height);
	bmi = weight/(height*height);
	printf("Du veier %f kilo og er %f meter høy.\n"
	       "Det gir en BMI på %d.\n", weight, height, bmi);
	return (0);
}

