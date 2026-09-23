# Architecture

The library defines two shared capabilities: FileStorage and KeyValueStorage. There is deliberately no generic ancestor that erases meaningful behavioural differences between the two.

All buffers are caller-owned at the contract boundary. Reads may successfully transfer less than the available logical value and report that fact explicitly; mutations must complete the requested logical mutation at the provider's advertised durability/atomicity level before success is returned.
