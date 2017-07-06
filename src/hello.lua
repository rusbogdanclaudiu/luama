print("hello")
print("world")

print(persistence.writes())
persistence.set_writes(100);
print(persistence.readString("stringKey"))
print(persistence.readInt("intKey"))
print(persistence.writeString("stringKey", "mykey"))
print(persistence.writes())