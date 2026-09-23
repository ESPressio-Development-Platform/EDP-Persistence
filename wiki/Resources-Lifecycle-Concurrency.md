# Resources, Lifecycle and Concurrency

The abstract contracts allocate no buffers and retain no caller data. Concurrency, durability and failure preservation are provider facts. Retention orders Session < Restart < PowerLoss. InterruptionAtomicity cannot truthfully exceed retention. No blanket ISR guarantee exists.
