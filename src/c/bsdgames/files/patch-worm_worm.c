--- worm/worm.c.orig	2016-05-14 12:55:57 UTC
+++ worm/worm.c
@@ -215,9 +215,17 @@ process(char ch)
 	switch(ch)
 	{
 		case 'h': x--; break;
+	        case 'a': x--; break;
 		case 'j': y++; break;
+	        case 's': y++; break;
 		case 'k': y--; break;
+	        case 'w': y--; break;
 		case 'l': x++; break;
+	        case 'd': x++; break;
+		case 'A': x--; running = RUNLEN; ch = tolower(ch); break;
+		case 'S': y++; running = RUNLEN/2; ch = tolower(ch); break;
+		case 'W': y--; running = RUNLEN/2; ch = tolower(ch); break;
+		case 'D': x++; running = RUNLEN; ch = tolower(ch); break;
 		case 'H': x--; running = RUNLEN; ch = tolower(ch); break;
 		case 'J': y++; running = RUNLEN/2; ch = tolower(ch); break;
 		case 'K': y--; running = RUNLEN/2; ch = tolower(ch); break;
