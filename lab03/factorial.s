.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    # Save any callee-saved registers
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    # Main body of the function
    addi s0, x0, 1
    loop:
        beq a0, x0, return
        # The full version should use mul and mulh
        mul s0, s0, a0
        addi a0, a0, -1
        j loop  # jump to loop
        

    return:
        add a0, s0, x0
        lw s0, 4(sp)
        lw ra, 0(sp)
        addi sp, sp, 8
        jr ra
