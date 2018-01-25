#pragma once

#include <avr/pgmspace.h>

// macros to generate the PARITY_8_BIT lookup table (at compile-time)
#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n), P2(n ^ 1), P2(n ^ 1), P2(n)
#define P6(n) P4(n), P4(n ^ 1), P4(n ^ 1), P4(n)
#define PARITY_8_BIT P6(0), P6(1), P6(1), P6(0)

// macros to generate the COUNT_BITS lookup table (at compile-time)
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)

#define COUNT_BITS_8BITS_TABLE B6(0), B6(1), B6(1), B6(2)
#define COUNT_BITS_7BITS_TABLE B6(0), B6(1)
#define COUNT_BITS_6BITS_TABLE B6(0)
#define COUNT_BITS_5BITS_TABLE B4(0), B4(1)
#define COUNT_BITS_4BITS_TABLE B4(0)

// LOOK_UP is the macro expansion to generate the table
//const uint8_t BitsSetTable_4Bits[] PROGMEM = { COUNT_BITS_4BITS_TABLE };
//const uint8_t BitsSetTable_5Bits[] PROGMEM = { COUNT_BITS_5BITS_TABLE };
//const uint8_t BitsSetTable_6Bits[] PROGMEM = { COUNT_BITS_6BITS_TABLE };
//const uint8_t BitsSetTable_7Bits[] PROGMEM = { COUNT_BITS_7BITS_TABLE };
//const uint8_t BitsSetTable_8Bits[] PROGMEM = { COUNT_BITS_8BITS_TABLE };

inline uint8_t count_bits(uint8_t value, const uint8_t NumberOfBits, const uint8_t BitsSetTable[]) __attribute__((always_inline));
inline uint8_t parity(uint8_t value, const uint8_t BitsSetTable[]) __attribute__((always_inline));

inline uint8_t count_bits_progmem(uint8_t value, const uint8_t NumberOfBits, const uint8_t BitsSetTable[]) __attribute__((always_inline));
inline uint8_t parity_progmem(uint8_t value, const uint8_t BitsSetTable[]) __attribute__((always_inline));

uint8_t parity_progmem(uint8_t value, const uint8_t parityTable[])
{
	return pgm_read_byte_near(parityTable + value);
}

uint8_t count_bits_progmem(uint8_t value, const uint8_t NumberOfBits, const uint8_t BitsSetTable[])
{
	return pgm_read_byte_near(BitsSetTable + (value & (_BV(NumberOfBits) - 1)));
}

uint8_t parity(uint8_t value, const uint8_t parityTable[])
{
	return parityTable[value];
}

uint8_t count_bits(uint8_t value, const uint8_t NumberOfBits, const uint8_t BitsSetTable[])
{
	return BitsSetTable[value & (_BV(NumberOfBits) - 1)];
}

// Count Bits Table
/*
0, 0
1, 1
2, 1
3, 2
4, 1
5, 2
6, 2
7, 3
8, 1
9, 2
10, 2
11, 3
12, 2
13, 3
14, 3
15, 4
16, 1
17, 2
18, 2
19, 3
20, 2
21, 3
22, 3
23, 4
24, 2
25, 3
26, 3
27, 4
28, 3
29, 4
30, 4
31, 5
32, 1
33, 2
34, 2
35, 3
36, 2
37, 3
38, 3
39, 4
40, 2
41, 3
42, 3
43, 4
44, 3
45, 4
46, 4
47, 5
48, 2
49, 3
50, 3
51, 4
52, 3
53, 4
54, 4
55, 5
56, 3
57, 4
58, 4
59, 5
60, 4
61, 5
62, 5
63, 6
64, 1
65, 2
66, 2
67, 3
68, 2
69, 3
70, 3
71, 4
72, 2
73, 3
74, 3
75, 4
76, 3
77, 4
78, 4
79, 5
80, 2
81, 3
82, 3
83, 4
84, 3
85, 4
86, 4
87, 5
88, 3
89, 4
90, 4
91, 5
92, 4
93, 5
94, 5
95, 6
96, 2
97, 3
98, 3
99, 4
100, 3
101, 4
102, 4
103, 5
104, 3
105, 4
106, 4
107, 5
108, 4
109, 5
110, 5
111, 6
112, 3
113, 4
114, 4
115, 5
116, 4
117, 5
118, 5
119, 6
120, 4
121, 5
122, 5
123, 6
124, 5
125, 6
126, 6
127, 7
128, 1
129, 2
130, 2
131, 3
132, 2
133, 3
134, 3
135, 4
136, 2
137, 3
138, 3
139, 4
140, 3
141, 4
142, 4
143, 5
144, 2
145, 3
146, 3
147, 4
148, 3
149, 4
150, 4
151, 5
152, 3
153, 4
154, 4
155, 5
156, 4
157, 5
158, 5
159, 6
160, 2
161, 3
162, 3
163, 4
164, 3
165, 4
166, 4
167, 5
168, 3
169, 4
170, 4
171, 5
172, 4
173, 5
174, 5
175, 6
176, 3
177, 4
178, 4
179, 5
180, 4
181, 5
182, 5
183, 6
184, 4
185, 5
186, 5
187, 6
188, 5
189, 6
190, 6
191, 7
192, 2
193, 3
194, 3
195, 4
196, 3
197, 4
198, 4
199, 5
200, 3
201, 4
202, 4
203, 5
204, 4
205, 5
206, 5
207, 6
208, 3
209, 4
210, 4
211, 5
212, 4
213, 5
214, 5
215, 6
216, 4
217, 5
218, 5
219, 6
220, 5
221, 6
222, 6
223, 7
224, 3
225, 4
226, 4
227, 5
228, 4
229, 5
230, 5
231, 6
232, 4
233, 5
234, 5
235, 6
236, 5
237, 6
238, 6
239, 7
240, 4
241, 5
242, 5
243, 6
244, 5
245, 6
246, 6
247, 7
248, 5
249, 6
250, 6
251, 7
252, 6
253, 7
254, 7
255, 8
*/