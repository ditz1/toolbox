import mysql.connector
from mysql.connector import Error

def create_connection():
    try:
        connection = mysql.connector.connect(
            host='127.0.0.1',
            database='testingdb',
            user='root',
            password='root'
        )
        return connection
    except Error as e:
        print(f"error connecting to SQL database: {e}")
        return None


def insert_entry(length, width, height, tag=None):
    connection = create_connection()
    if connection is None:
        return

    try:
        cursor = connection.cursor()
        
        insert_global = "INSERT INTO global (tag) VALUES (%s)"
        cursor.execute(insert_global, (tag,))
        global_id = cursor.lastrowid

        insert_measurement = "INSERT INTO {} (global_id, {}) VALUES (%s, %s)"
        cursor.execute(insert_measurement.format('lengths', 'length'), (global_id, length))
        cursor.execute(insert_measurement.format('widths', 'width'), (global_id, width))
        cursor.execute(insert_measurement.format('heights', 'height'), (global_id, height))

        connection.commit()
        print("-- entry inserted successfully --\n")
    except Error as e:
        print(f"Error: {e}")
    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()


def get_entry(length=None, width=None, height=None, tag=None):
    connection = create_connection()
    if connection is None:
        return

    try:
        cursor = connection.cursor(dictionary=True)
        
        query = """
        SELECT g.id, g.date_created, g.tag, l.length, w.width, h.height
        FROM global g
        LEFT JOIN lengths l ON g.id = l.global_id
        LEFT JOIN widths w ON g.id = w.global_id
        LEFT JOIN heights h ON g.id = h.global_id
        WHERE 1=1
        """
        params = []

        if length is not None and length != '':
            query += " AND l.length = %s"
            params.append(float(length))
        if width is not None and width != '':
            query += " AND w.width = %s"
            params.append(float(width))
        if height is not None and height != '':
            query += " AND h.height = %s"
            params.append(float(height))
        if tag is not None and tag != '':
            query += " AND g.tag LIKE %s"
            params.append(f"%{tag}%")

        cursor.execute(query, params)
        results = cursor.fetchall()
        if len(results) == 0:
            print("-- no entries found --\n")
            return None
        else:
            formatted_results = format_query_results(results)
            print("number of entries found: ", len(results))
            print(formatted_results)
            return results
        

    except Error as e:
        print(f"error: {e}")

    finally:
        if connection.is_connected():
            cursor.close()
            connection.close()


def make_new_entry():
    print("enter the following information for the new entry:")
    while True:
        try:
            length = input("length: ")
            width = input("width: ")
            height = input("height: ")
            tag = input("tag (optional): ")

            if not length or not width or not height:
                print("\ninvalid entry: length, width, and height must be given")
                break

            length = float(length)
            width = float(width)
            height = float(height)

            if tag == '':
                tag = None

            print(f"inserted new entry:\n   l = {length}, w = {width}, h = {height}, tag = {tag}")
            insert_entry(length, width, height, tag)
            break
        except ValueError:
            print("invalid input: length, width, and height must be numbers")
            break
        except Exception as e:
            print(f"an error occurred: {e}")
            break

def query_db():
    print("enter the following information to query the database:")
    while True:
        try:
            length = input("length (optional): ")
            width = input("width (optional): ")
            height = input("height (optional): ")
            tag = input("tag (optional): ")

            length = float(length) if length else None
            width = float(width) if width else None
            height = float(height) if height else None
            tag = tag if tag else None

            print(f"queried for:\n l = {length}, w = {width}, h = {height}, tag = {tag}\n")
            get_entry(length, width, height, tag)
            break
        except ValueError:
            print("invalid input: length, width, and height must be numbers if provided")
            break
        except Exception as e:
            print(f"an error occurred: {e}")
            break


def format_query_results(results):
    if not results:
        return "no entries found"

    formatted_output = ""
    for row in results:
        formatted_output += "-" * 40 + "\n"
        formatted_output += f"id: {row['id']} | "
        formatted_output += f"date: {row['date_created']} | "
        formatted_output += f"tag: {row['tag'] if row['tag'] else 'N/A'}\n"
        formatted_output += f"length: {row['length']:.2f} | "
        formatted_output += f"width: {row['width']:.2f} | "
        formatted_output += f"height: {row['height']:.2f}\n"
    formatted_output += "-" * 40 + "\n"
    return formatted_output


def main():
    while(True):
        entry = input("query, insert, or exit ([q]/[i]/[e]):  ")
        if entry == 'i' or entry == 'insert':
            print("selected insert...\n")
            make_new_entry()
        elif entry == 'q' or entry == 'query':
            print("selected query...\n")
            query_db()
        elif entry == 'e' or entry == 'exit':
            print("\n goodbye...\n")
            break
        else:
            print("\n invalid command (q : query, i : insert, e : exit)\n")
    
    #insert_entry(10.5, 20.0, 30.0, "Sample measurement")
    #get_entry(length=10.5)
    #get_entry(width=20.0, tag="Sample measurement")

if __name__ == "__main__":
    main()    
