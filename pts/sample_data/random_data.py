# this Python script generates random Congregation, Speaker and Talk names and puts
# them in CSV files. `text/congs.txt`, `text/names.txt` and `text/words.txt` are
# provided as sample word/name sources for this script. You can find sample results
# in this folder (sampleData)
import random

word_list = []

TOTAL_CONGREGATIONS = 20
TOTAL_TALKS = 50
TOTAL_ELDERS = 40

############## ID and talk_title csv ###############
word_file = open('text/words.txt')
csv_file  = open('random_talks.csv', 'w')

generated_talk_numbers = []

for word in word_file:
    word_list.append(word)

csv_file.write('id,' + 'talk_number,' + 'title' + '\n')
for i in range(1, TOTAL_TALKS):
    id = str(i)
    talk_number = str(random.randint(1, TOTAL_TALKS))

    while talk_number in generated_talk_numbers:
        talk_number = str(random.randint(1, TOTAL_TALKS))

    generated_talk_numbers.append(talk_number)
    first_word  = random.choice(word_list).rstrip('\n')
    middle_word = random.choice(word_list).rstrip('\n')
    last_word   = random.choice(word_list).rstrip('\n')
    csv_file.write(id + ',' + talk_number + ',' + first_word.title() + " " + middle_word.title() + " " + last_word.title() + '\n')

print('talkTitle_csv successfuly created...')
############## ID and cong_name csv ################
word_file = open('text/congs.txt')
csv_file  = open('random_congs.csv', 'w')
generated_cong_ids = []

word_list.clear()
for word in word_file:
    word_list.append(word)

csv_file.write('id,' + 'name' + '\n')
for i in range(1, TOTAL_CONGREGATIONS):
    cong_name = random.choice(word_list).rstrip('\n')
    csv_file.write(str(i) + ',' + cong_name + '\n')
    generated_cong_ids.append(str(i))

print('cong_csv successfuly created...')
############## ID and elder_detail csv #############
#id firstName    middleName    lastName    phoneNumber    talk_id    congregation_id enabled
word_file = open('text/names.txt')
csv_file  = open('random_elders.csv', 'w')

elder_talk_dict = {}

word_list.clear()
for word in word_file:
    word_list.append(word)

csv_file.write('id,' + 'first_name,' + 'middle_name,' + 'last_name,' + 'phone_number,'\
                + 'talk_id,' + 'congregation_id,' + 'enabled' + '\n')
for i in range(1, TOTAL_ELDERS):
    _id             = str(i)
    talk_id         = random.choice(generated_talk_numbers)

    while talk_id in elder_talk_dict.values():
        talk_id = str(random.choice(generated_talk_numbers))

    elder_talk_dict[_id] = talk_id
    first_name      = random.choice(word_list).rstrip('\n')
    middle_name     = random.choice(word_list).rstrip('\n')
    last_name       = random.choice(word_list).rstrip('\n')
    phoneNumber     = '09' \
                      + str(random.randint(0, 9)) + str(random.randint(0, 9)) \
                      + str(random.randint(0, 9)) + str(random.randint(0, 9)) \
                      + str(random.randint(0, 9)) + str(random.randint(0, 9)) \
                      + str(random.randint(0, 9)) + str(random.randint(0, 9))
    congregation_id = str(random.choice(generated_cong_ids))
    enabled         = 1
    csv_file.write(_id + ',' + first_name + ',' + middle_name + ',' + last_name + ','
                    + phoneNumber + ',' + talk_id + ',' + congregation_id + ',' + str(enabled) + '\n')

print('elder_csv successfuly created...')

# insert into the database
import csv, sqlite3

con = sqlite3.connect("../../build-pts-Desktop-Debug/pts.bin")
cur = con.cursor()

# clear existing data
cur.execute("DELETE FROM talk;")
cur.execute("DELETE FROM Congregation;")
cur.execute("DELETE FROM elder;")

# insert new data
with open('random_talks.csv','r') as csv_file:
    dr = csv.DictReader(csv_file)
    tuples = [(pair['id'], pair['talk_number'], pair['title']) for pair in dr]
    cur.executemany("INSERT INTO talk (id, talk_number, title) VALUES (?, ?, ?);", tuples)
print("talk table populated...")

with open('random_congs.csv','r') as csv_file:
    dr = csv.DictReader(csv_file)
    tuples = [(pair['id'], pair['name']) for pair in dr]
    cur.executemany("INSERT INTO congregation (id, name) VALUES (?, ?);", tuples)
print("congregation table populated...")

with open('random_elders.csv','r') as csv_file:
    dr = csv.DictReader(csv_file)
    tuples = [(pair['id'], pair['first_name'], pair['middle_name'], pair['last_name'], pair['phone_number'], pair['talk_id'], pair['congregation_id'], pair['enabled']) for pair in dr]
    cur.executemany("INSERT INTO elder (id, first_name, middle_name, last_name, phone_number, talk_id, congregation_id, enabled) VALUES (?, ?, ?, ?, ?, ?, ?, ?);", tuples)
print("elder table populated")

con.commit()
con.close()
