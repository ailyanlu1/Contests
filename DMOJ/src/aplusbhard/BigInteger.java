package aplusbhard;

public class BigInteger implements Comparable<BigInteger> {
	public static final BigInteger ZERO = new BigInteger(new byte[]{0}, false);
    public static final BigInteger ONE = new BigInteger(new byte[]{1}, false);
    private final byte[] digits;
    private final boolean isNegative;
	public BigInteger(byte[] digits, boolean isNegative) {
        this.digits = digits;
        this.isNegative = isNegative;
    }
    public BigInteger add(BigInteger other) {
        byte[] digits1, digits2;
        if (this.digits.length >= other.digits.length) {
            digits1 = this.digits;
            digits2 = other.digits;
        } else {
            digits1 = other.digits;
            digits2 = this.digits;
        }
        int remainder = 0;
        int s1 = digits1.length;
        int s2 = digits2.length;
        byte[] resultDigits = new byte[s1+1];
        for (int i = 0; i < s1; i++) {
            int digit1 = digits1[i];
            int digit2 = i >= s2 ? 0 : digits2[i];
            int r = digit1 + digit2 + remainder;
            remainder = r > 9 ? 1 : 0;
            resultDigits[i] = (byte) (r % 10);
        }
        resultDigits[s1] = (byte) remainder;
        if (this.isNegative && other.isNegative) {
        	return new BigInteger(resultDigits, true);
        }
        return new BigInteger(resultDigits, false);
    }
    @Override
    public boolean equals(Object other) {
        if (!(other instanceof BigInteger)) return false;
        byte[] digits1 = this.digits;
        byte[] digits2 = ((BigInteger) other).getDigits();
        if (digits1.length != digits2.length) return false;
        for (int i = 0; i < digits1.length; i++) {
            if (digits1[i] != digits2[i]) return false;
        }
        return true;
    }
    @Override
    public int compareTo(BigInteger other) {
        byte[] digits1 = this.digits;
        byte[] digits2 = other.getDigits();
        int nzLength1 = digits1.length;
        int nzLength2 = digits2.length;
        for (int i = nzLength1 - 1; i >= 0; i--) {
            if (digits1[i] != 0) break;
            nzLength1--;
        }
        for (int i = nzLength2 - 1; i >= 0; i--) {
            if (digits2[i] != 0) break;
            nzLength2--;
        }
        if (nzLength1 > nzLength2) return 1;
        else if (nzLength1 < nzLength2) return -1;
        else {
            for (int i = nzLength1 - 1; i >= 0; i--) {
                if (digits1[i] == digits2[i]) continue;
                else if (digits1[1] > digits2[i]) return 1;
                else return -1;
            }
        }
        return 0;
    }
    public BigInteger subtract(BigInteger other) {
        boolean isNegative = this.compareTo(other) < 0;
        byte[] digits1, digits2;
        if (!isNegative) {
            digits1 = this.digits;
            digits2 = other.digits;
        } else {
            digits1 = other.digits;
            digits2 = this.digits;
        }
        int remainder = 0;
        int s1 = digits1.length;
        int s2 = digits2.length;
        byte[] resultDigits = new byte[s1+1];
        for (int i = 0; i < s1; i++) {
            int digit1 = digits1[i];
            int digit2 = i >= s2 ? 0 : digits2[i];
            int r = 10 + digit1 - digit2 - remainder;
            remainder = r > 9 ? 1 : 0;
            resultDigits[i] = (byte) (r % 10);
        }
        resultDigits[s1] = (byte) remainder;
        return new BigInteger(resultDigits, isNegative);
    }
    public byte[] getDigits() {
    	return this.digits;
    }
    public boolean isNegative() {
    	return this.isNegative;
    }
    @Override
    public String toString() {
    	String str = "";
    	if (this.isNegative) {
    		str += "-";
    	}
    	for (int i = digits.length - 1; i >= 0; i--) {
    		if (digits[i] != 0) str += digits[i];
    	}
    	return str;
    }
}
