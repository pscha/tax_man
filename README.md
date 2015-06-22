tax_man
=======

tax_man is a program that implements the tax_collectors from the tax_collectors
dillemma.

The tax collectors dilemma describes a situation where tax collectors are
implemented as threads and have a budget. Every tax collector wants to collect
taxes, from the other tax collectors, in height of half the others budget
rounded up to the next 100. While the other is unable to pay, because he has not
enougth budget the collecting collector waits until the other has the budget to
pay him.
