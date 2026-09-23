# Private Implementation

Read results separate logical status, success facts, transferred bytes and available logical data size. On failure, consumable facts/counts are normalized rather than leaving stale success-looking values.

Enumeration is synchronous/incremental with a caller-reusable buffer and noexcept Continue/Stop callback. UTF-8 name truncation must preserve code-point boundaries. InvocationConcurrency describes safe simultaneous invocation, not necessarily physical parallelism.
