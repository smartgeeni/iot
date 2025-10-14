import sqlite3

# Connect to SQLite database file (creates file if it doesn't exist)
conn = sqlite3.connect('sensor_data.sqlite')
cursor = conn.cursor()

# Create table with UNIQUE constraint on timestamp
cursor.execute('''
CREATE TABLE IF NOT EXISTS sensor_readings (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp TEXT UNIQUE,
    temperature REAL,
    humidity REAL
)
''')

# Dummy data with timestamps (same as before)
dummy_data = [
    ('2025-10-03 10:00:00', 22.5, 55.2),
    ('2025-10-03 10:05:00', 22.7, 54.8),
    ('2025-10-03 10:10:00', 22.6, 55.0),
    ('2025-10-03 10:15:00', 22.8, 54.5),
]

# Insert data using INSERT OR IGNORE to skip duplicates
cursor.executemany('''
INSERT OR IGNORE INTO sensor_readings (timestamp, temperature, humidity)
VALUES (?, ?, ?)
''', dummy_data)

conn.commit()

# Retrieve and print all rows from the table
cursor.execute("SELECT * FROM sensor_readings")
rows = cursor.fetchall()

for row in rows:
    print(row)

conn.close()

