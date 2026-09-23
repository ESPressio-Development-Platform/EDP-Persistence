# Composition

FileStorage and KeyValueStorage are shared Persistence-domain capabilities. Concrete providers declare their semantic properties so consumers can qualify Requirements at compile time.

Optional operations are part of the provider type only when advertised as Supported. Read-only providers keep mandatory mutation entry points but return ReadOnly; unsupported optional mutation surfaces are absent rather than pretending to fail dynamically.
