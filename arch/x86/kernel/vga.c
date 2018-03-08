#include <swiros/string.h>
#include <asm/io.h>
#include <asm/vga.h>

static unsigned short *textmemptr;
static int attrib = 0x0F;
static int csr_x = 0, csr_y = 0;

inline static unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
	size_t i;
	
	if (BUILTIN_EXPECT(!dest, 0))
		return dest;
		
	for (i = 0; i < count; i++)
		dest[i] = val;
		
	return dest;
}

static void scroll(void)
{
	unsigned blank, temp;

	/* 
	 * A blank is defined as a space... we need to give it
	 * backcolor too 
	 */
	blank = 0x20 | (attrib << 8);

	/* Row 25 is the end, this means we need to scroll up */
	if (csr_y >= 25) {

		/* 
		 * Move the current text chunk that makes up the screen
		 *  
		 * back in the buffer by one line 
		 */
		temp = csr_y - 25 + 1;
		memcpy(textmemptr, textmemptr + temp * 80,
		       (25 - temp) * 80 * 2);

		/* 
		 * Finally, we set the chunk of memory that occupies
		 * the last line of text to our 'blank' character 
		 */
		memsetw(textmemptr + (25 - temp) * 80, blank, 80);
		csr_y = 25 - 1;
	}
}

/* 
 * Updates the hardware cursor: the little blinking line
 * on the screen under the last character pressed! 
 */
static void move_csr(void)
{
	unsigned temp;

	/* 
	 * The equation for finding the index in a linear
	 * chunk of memory can be represented by:
	 * Index = [(y * width) + x] */
	temp = csr_y * 80 + csr_x;
	
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

/* Clears the screen */
void vga_clear(void)
{
	unsigned blank;
	int i;

	/*
	 * Again, we need the 'short' that will be used to
	 * represent a space with color 
	 */
	blank = 0x20 | (attrib << 8);

	/* 
	 * Fills the entire screen with spaces in our current
	 * color 
	 **/
	for (i = 0; i < 25; i++)
		memsetw(textmemptr + i * 80, blank, 80);

	/* 
	 * Update out virtual cursor, and then move the
	 * hardware cursor 
	 */
	csr_x = 0;
	csr_y = 0;
	move_csr();
}

/* Puts a single character on the screen */
int vga_putchar(unsigned char c)
{
	unsigned short *where;
	unsigned att = attrib << 8;

	/* Handle a backspace by moving the cursor back one space */
	if (c == 0x08) {
		if (csr_x != 0)
			csr_x--;
	}

	/* 
	 * Handles a tab by incrementing the cursor's x, but only
	 * to a point that will make it divisible by 8 
	 */
	else if (c == 0x09) {
		csr_x = (csr_x + 8) & ~(8 - 1);
	}

	/* 
	 * Handles a 'Carriage Return', which simply brings the
	 * cursor back to the margin 
	 */
	else if (c == '\r') {
		csr_x = 0;
	}

	/* 
	 * We handle our newlines the way DOS and BIOS do: we
	 * treat it as if a 'CR' was there also, so we bring the
	 * cursor to the margin and increment the 'y' value 
	 */
	else if (c == '\n') {
		csr_x = 0;
		csr_y++;
	}

	/* 
	 * Any character greater than and including the space is a
	 * printable character. The equation for finding the index
	 * in a linear chunk of memory can be represented by:
	 * Index = [(y * width) + x] 
	 */
	else if (c >= ' ') {
		where = textmemptr + (csr_y * 80 + csr_x);
		*where = c | att;	/* Character AND attributes: color */
		csr_x++;
	}

	/* 
	 * If the cursor has reached the edge of the screen's width, we
	 * insert a new line in there 
	 */
	if (csr_x >= 80) {
		csr_x = 0;
		csr_y++;
	}

	/* Scroll the screen if needed, and finally move the cursor */
	scroll();
	move_csr();

	return (int) c;
}

/* Uses the routine above to output a string... */
int vga_puts(const char *text)
{
	size_t i;

	for (i = 0; i < strlen(text); i++)
		vga_putchar(text[i]);

	return i-1;
}

//void settextcolor(unsigned char forecolor, unsigned char backcolor)
//{

//	attrib = (backcolor << 4) | (forecolor & 0x0F);
//}

void vga_init(void)
{
	textmemptr = (unsigned short *)VIDEO_MEM_ADDR;
	vga_clear();
}

