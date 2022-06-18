

#define		SET_BIT(REG,BIT)		 ( (REG) |= (1 << (BIT)))
#define		CLR_BIT(REG,BIT)		 ( (REG) &= (~ ( 1 << (BIT) ) ))
#define		TOG_BIT(REG,BIT)		 ( (REG) ^= (1<<(BIT)))
#define		GET_BIT(REG,BIT)		 ( ( (REG) & (1<< (BIT) ) ) >> (BIT) )

