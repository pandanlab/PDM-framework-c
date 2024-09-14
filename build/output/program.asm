
build/output/program.elf:     file format elf32-littlearm


Disassembly of section .text:

08000000 <vectors>:
 8000000:	00 50 00 20 95 02 00 08 91 02 00 08 91 02 00 08     .P. ............
 8000010:	91 02 00 08 91 02 00 08 91 02 00 08 00 00 00 00     ................
	...
 800002c:	91 02 00 08 91 02 00 08 00 00 00 00 91 02 00 08     ................
 800003c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800004c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800005c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800006c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800007c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800008c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800009c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000ac:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000bc:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000cc:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000dc:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000ec:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 80000fc:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800010c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800011c:	91 02 00 08 91 02 00 08 91 02 00 08 91 02 00 08     ................
 800012c:	91 02 00 08 91 02 00 08                             ........

08000134 <pinMode>:
 8000134:	2907      	cmp	r1, #7
 8000136:	ea42 0283 	orr.w	r2, r2, r3, lsl #2
 800013a:	d80c      	bhi.n	8000156 <pinMode+0x22>
 800013c:	f04f 0c0f 	mov.w	ip, #15
 8000140:	0089      	lsls	r1, r1, #2
 8000142:	6803      	ldr	r3, [r0, #0]
 8000144:	b2c9      	uxtb	r1, r1
 8000146:	408a      	lsls	r2, r1
 8000148:	fa0c f101 	lsl.w	r1, ip, r1
 800014c:	ea23 0101 	bic.w	r1, r3, r1
 8000150:	430a      	orrs	r2, r1
 8000152:	6002      	str	r2, [r0, #0]
 8000154:	4770      	bx	lr
 8000156:	f04f 0c0f 	mov.w	ip, #15
 800015a:	3908      	subs	r1, #8
 800015c:	0089      	lsls	r1, r1, #2
 800015e:	6843      	ldr	r3, [r0, #4]
 8000160:	b2c9      	uxtb	r1, r1
 8000162:	408a      	lsls	r2, r1
 8000164:	fa0c f101 	lsl.w	r1, ip, r1
 8000168:	ea23 0101 	bic.w	r1, r3, r1
 800016c:	430a      	orrs	r2, r1
 800016e:	6042      	str	r2, [r0, #4]
 8000170:	4770      	bx	lr
 8000172:	bf00      	nop

08000174 <digitalWritePin>:
 8000174:	b132      	cbz	r2, 8000184 <digitalWritePin+0x10>
 8000176:	2301      	movs	r3, #1
 8000178:	68c2      	ldr	r2, [r0, #12]
 800017a:	fa03 f101 	lsl.w	r1, r3, r1
 800017e:	4311      	orrs	r1, r2
 8000180:	60c1      	str	r1, [r0, #12]
 8000182:	4770      	bx	lr
 8000184:	2201      	movs	r2, #1
 8000186:	68c3      	ldr	r3, [r0, #12]
 8000188:	fa02 f101 	lsl.w	r1, r2, r1
 800018c:	ea23 0101 	bic.w	r1, r3, r1
 8000190:	60c1      	str	r1, [r0, #12]
 8000192:	4770      	bx	lr

08000194 <digitalWritePort>:
 8000194:	60c1      	str	r1, [r0, #12]
 8000196:	4770      	bx	lr

08000198 <uart_printf>:
 8000198:	b570      	push	{r4, r5, r6, lr}
 800019a:	4e05      	ldr	r6, [pc, #20]	; (80001b0 <uart_printf+0x18>)
 800019c:	1e45      	subs	r5, r0, #1
 800019e:	f815 4f01 	ldrb.w	r4, [r5, #1]!
 80001a2:	4630      	mov	r0, r6
 80001a4:	4621      	mov	r1, r4
 80001a6:	f000 f8a5 	bl	80002f4 <uart_write>
 80001aa:	2c00      	cmp	r4, #0
 80001ac:	d1f7      	bne.n	800019e <uart_printf+0x6>
 80001ae:	bd70      	pop	{r4, r5, r6, pc}
 80001b0:	40013800 	.word	0x40013800

080001b4 <uart_readString>:
 80001b4:	b159      	cbz	r1, 80001ce <uart_readString+0x1a>
 80001b6:	b570      	push	{r4, r5, r6, lr}
 80001b8:	4604      	mov	r4, r0
 80001ba:	4e05      	ldr	r6, [pc, #20]	; (80001d0 <uart_readString+0x1c>)
 80001bc:	1845      	adds	r5, r0, r1
 80001be:	4630      	mov	r0, r6
 80001c0:	f000 f8a4 	bl	800030c <uart_read>
 80001c4:	f804 0b01 	strb.w	r0, [r4], #1
 80001c8:	42ac      	cmp	r4, r5
 80001ca:	d1f8      	bne.n	80001be <uart_readString+0xa>
 80001cc:	bd70      	pop	{r4, r5, r6, pc}
 80001ce:	4770      	bx	lr
 80001d0:	40013800 	.word	0x40013800

080001d4 <main>:
 80001d4:	b580      	push	{r7, lr}
 80001d6:	b084      	sub	sp, #16
 80001d8:	466c      	mov	r4, sp
 80001da:	466d      	mov	r5, sp
 80001dc:	2002      	movs	r0, #2
 80001de:	f000 f843 	bl	8000268 <rcc_apb2_enable>
 80001e2:	200e      	movs	r0, #14
 80001e4:	f000 f840 	bl	8000268 <rcc_apb2_enable>
 80001e8:	230a      	movs	r3, #10
 80001ea:	2209      	movs	r2, #9
 80001ec:	4916      	ldr	r1, [pc, #88]	; (8000248 <main+0x74>)
 80001ee:	4817      	ldr	r0, [pc, #92]	; (800024c <main+0x78>)
 80001f0:	f000 f854 	bl	800029c <uart_init>
 80001f4:	4b16      	ldr	r3, [pc, #88]	; (8000250 <main+0x7c>)
 80001f6:	4e15      	ldr	r6, [pc, #84]	; (800024c <main+0x78>)
 80001f8:	cb0f      	ldmia	r3, {r0, r1, r2, r3}
 80001fa:	c407      	stmia	r4!, {r0, r1, r2}
 80001fc:	8023      	strh	r3, [r4, #0]
 80001fe:	f815 4b01 	ldrb.w	r4, [r5], #1
 8000202:	4630      	mov	r0, r6
 8000204:	4621      	mov	r1, r4
 8000206:	f000 f875 	bl	80002f4 <uart_write>
 800020a:	2c00      	cmp	r4, #0
 800020c:	d1f7      	bne.n	80001fe <main+0x2a>
 800020e:	4d0f      	ldr	r5, [pc, #60]	; (800024c <main+0x78>)
 8000210:	f10d 0705 	add.w	r7, sp, #5
 8000214:	4628      	mov	r0, r5
 8000216:	f000 f859 	bl	80002cc <uart_statusRead>
 800021a:	2801      	cmp	r0, #1
 800021c:	d1fa      	bne.n	8000214 <main+0x40>
 800021e:	466c      	mov	r4, sp
 8000220:	4628      	mov	r0, r5
 8000222:	f000 f873 	bl	800030c <uart_read>
 8000226:	f804 0b01 	strb.w	r0, [r4], #1
 800022a:	42bc      	cmp	r4, r7
 800022c:	d1f8      	bne.n	8000220 <main+0x4c>
 800022e:	466e      	mov	r6, sp
 8000230:	f816 4b01 	ldrb.w	r4, [r6], #1
 8000234:	4628      	mov	r0, r5
 8000236:	4621      	mov	r1, r4
 8000238:	f000 f85c 	bl	80002f4 <uart_write>
 800023c:	2c00      	cmp	r4, #0
 800023e:	d1f7      	bne.n	8000230 <main+0x5c>
 8000240:	4628      	mov	r0, r5
 8000242:	f000 f84b 	bl	80002dc <uart_resetRead>
 8000246:	e7e5      	b.n	8000214 <main+0x40>
 8000248:	40010800 	.word	0x40010800
 800024c:	40013800 	.word	0x40013800
 8000250:	0800034c 	.word	0x0800034c

08000254 <rcc_ahb_enable>:
 8000254:	2301      	movs	r3, #1
 8000256:	4a03      	ldr	r2, [pc, #12]	; (8000264 <rcc_ahb_enable+0x10>)
 8000258:	4083      	lsls	r3, r0
 800025a:	6951      	ldr	r1, [r2, #20]
 800025c:	430b      	orrs	r3, r1
 800025e:	6153      	str	r3, [r2, #20]
 8000260:	4770      	bx	lr
 8000262:	bf00      	nop
 8000264:	40021000 	.word	0x40021000

08000268 <rcc_apb2_enable>:
 8000268:	2301      	movs	r3, #1
 800026a:	4a03      	ldr	r2, [pc, #12]	; (8000278 <rcc_apb2_enable+0x10>)
 800026c:	4083      	lsls	r3, r0
 800026e:	6991      	ldr	r1, [r2, #24]
 8000270:	430b      	orrs	r3, r1
 8000272:	6193      	str	r3, [r2, #24]
 8000274:	4770      	bx	lr
 8000276:	bf00      	nop
 8000278:	40021000 	.word	0x40021000

0800027c <rcc_apb1_enable>:
 800027c:	2301      	movs	r3, #1
 800027e:	4a03      	ldr	r2, [pc, #12]	; (800028c <rcc_apb1_enable+0x10>)
 8000280:	4083      	lsls	r3, r0
 8000282:	69d1      	ldr	r1, [r2, #28]
 8000284:	430b      	orrs	r3, r1
 8000286:	61d3      	str	r3, [r2, #28]
 8000288:	4770      	bx	lr
 800028a:	bf00      	nop
 800028c:	40021000 	.word	0x40021000

08000290 <ADC1_2_IRQHandler>:
 8000290:	e7fe      	b.n	8000290 <ADC1_2_IRQHandler>
 8000292:	bf00      	nop

08000294 <Reset_Handler>:
 8000294:	b508      	push	{r3, lr}
 8000296:	f7ff ff9d 	bl	80001d4 <main>
 800029a:	e7fe      	b.n	800029a <Reset_Handler+0x6>

0800029c <uart_init>:
 800029c:	b570      	push	{r4, r5, r6, lr}
 800029e:	460d      	mov	r5, r1
 80002a0:	461e      	mov	r6, r3
 80002a2:	4611      	mov	r1, r2
 80002a4:	4604      	mov	r4, r0
 80002a6:	2302      	movs	r3, #2
 80002a8:	2201      	movs	r2, #1
 80002aa:	4628      	mov	r0, r5
 80002ac:	f7ff ff42 	bl	8000134 <pinMode>
 80002b0:	2301      	movs	r3, #1
 80002b2:	2200      	movs	r2, #0
 80002b4:	4631      	mov	r1, r6
 80002b6:	4628      	mov	r0, r5
 80002b8:	f7ff ff3c 	bl	8000134 <pinMode>
 80002bc:	f240 3241 	movw	r2, #833	; 0x341
 80002c0:	f242 032c 	movw	r3, #8236	; 0x202c
 80002c4:	60a2      	str	r2, [r4, #8]
 80002c6:	60e3      	str	r3, [r4, #12]
 80002c8:	bd70      	pop	{r4, r5, r6, pc}
 80002ca:	bf00      	nop

080002cc <uart_statusRead>:
 80002cc:	6800      	ldr	r0, [r0, #0]
 80002ce:	f3c0 1040 	ubfx	r0, r0, #5, #1
 80002d2:	4770      	bx	lr

080002d4 <uart_statusWrite>:
 80002d4:	6800      	ldr	r0, [r0, #0]
 80002d6:	f3c0 1080 	ubfx	r0, r0, #6, #1
 80002da:	4770      	bx	lr

080002dc <uart_resetRead>:
 80002dc:	6803      	ldr	r3, [r0, #0]
 80002de:	f023 0320 	bic.w	r3, r3, #32
 80002e2:	6003      	str	r3, [r0, #0]
 80002e4:	4770      	bx	lr
 80002e6:	bf00      	nop

080002e8 <uart_resetWrite>:
 80002e8:	6803      	ldr	r3, [r0, #0]
 80002ea:	f043 0340 	orr.w	r3, r3, #64	; 0x40
 80002ee:	6003      	str	r3, [r0, #0]
 80002f0:	4770      	bx	lr
 80002f2:	bf00      	nop

080002f4 <uart_write>:
 80002f4:	6041      	str	r1, [r0, #4]
 80002f6:	6803      	ldr	r3, [r0, #0]
 80002f8:	065b      	lsls	r3, r3, #25
 80002fa:	d5fc      	bpl.n	80002f6 <uart_write+0x2>
 80002fc:	4a02      	ldr	r2, [pc, #8]	; (8000308 <uart_write+0x14>)
 80002fe:	6813      	ldr	r3, [r2, #0]
 8000300:	f043 0340 	orr.w	r3, r3, #64	; 0x40
 8000304:	6013      	str	r3, [r2, #0]
 8000306:	4770      	bx	lr
 8000308:	40013800 	.word	0x40013800

0800030c <uart_read>:
 800030c:	6803      	ldr	r3, [r0, #0]
 800030e:	069b      	lsls	r3, r3, #26
 8000310:	d5fc      	bpl.n	800030c <uart_read>
 8000312:	4a04      	ldr	r2, [pc, #16]	; (8000324 <uart_read+0x18>)
 8000314:	6840      	ldr	r0, [r0, #4]
 8000316:	6813      	ldr	r3, [r2, #0]
 8000318:	b2c0      	uxtb	r0, r0
 800031a:	f023 0320 	bic.w	r3, r3, #32
 800031e:	6013      	str	r3, [r2, #0]
 8000320:	4770      	bx	lr
 8000322:	bf00      	nop
 8000324:	40013800 	.word	0x40013800

08000328 <delay>:
 8000328:	f44f 727a 	mov.w	r2, #1000	; 0x3e8
 800032c:	2300      	movs	r3, #0
 800032e:	b082      	sub	sp, #8
 8000330:	fb02 f000 	mul.w	r0, r2, r0
 8000334:	9301      	str	r3, [sp, #4]
 8000336:	9b01      	ldr	r3, [sp, #4]
 8000338:	4298      	cmp	r0, r3
 800033a:	d905      	bls.n	8000348 <delay+0x20>
 800033c:	9b01      	ldr	r3, [sp, #4]
 800033e:	3301      	adds	r3, #1
 8000340:	9301      	str	r3, [sp, #4]
 8000342:	9b01      	ldr	r3, [sp, #4]
 8000344:	4283      	cmp	r3, r0
 8000346:	d3f9      	bcc.n	800033c <delay+0x14>
 8000348:	b002      	add	sp, #8
 800034a:	4770      	bx	lr
 800034c:	6c6c6568 	.word	0x6c6c6568
 8000350:	6f77206f 	.word	0x6f77206f
 8000354:	0d646c72 	.word	0x0d646c72
 8000358:	000a      	.short	0x000a