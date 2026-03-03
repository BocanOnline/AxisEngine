################################################################################
## organization: Bocan Online
## author: Matthew Buchanan
##
## license: The Unlicense
## project: AxisEngine
## app: AxisEngine-Core
## file: generator.py
##
## brief: Use this script to generate g-code files to test various 
##        functionality in AxisEngine.
##
## TODO:
##      [x] add arc function with variable radius and length
##      [x] add square function which uses the line function
##      [x] add start and end M-Code commands
##      [x] add a dialogue menu to provide user options
################################################################################
import sys
from math import sin, cos, pow, sqrt, pi, atan2
import os

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
GCODE_DIR = os.path.normpath(os.path.join(SCRIPT_DIR, "..", "gcode"))


class GCodeGenerator:
    def __init__(self):
        self.program = []
        self.operation_counter = 0
    
    def clear_program(self):
        self.program = []
        self.operation_counter = 0
    
    def add_start_mcode(self, code, speed=None):
        self.operation_counter += 1
        op = {
            'type': 'start_mcode',
            'id': self.operation_counter,
            'code': code,
            'speed': speed
        }
        self.program.append(op)
        return op
    
    def add_end_mcode(self, code):
        self.operation_counter += 1
        op = {
            'type': 'end_mcode',
            'id': self.operation_counter,
            'code': code
        }
        self.program.append(op)
        return op
    
    def add_circle(self, rad, x_pos, y_pos, num_seg):
        self.operation_counter += 1
        op = {
            'type': 'circle',
            'id': self.operation_counter,
            'rad': rad,
            'x_pos': x_pos,
            'y_pos': y_pos,
            'num_seg': num_seg
        }
        self.program.append(op)
        return op
    
    def add_line(self, x_start, y_start, x_end, y_end, num_seg):
        self.operation_counter += 1
        op = {
            'type': 'line',
            'id': self.operation_counter,
            'x_start': x_start,
            'y_start': y_start,
            'x_end': x_end,
            'y_end': y_end,
            'num_seg': num_seg
        }
        self.program.append(op)
        return op
    
    def add_iteration(self, shape_id, count, z_increment):
        self.operation_counter += 1
        op = {
            'type': 'iteration',
            'id': self.operation_counter,
            'shape_id': shape_id,
            'count': count,
            'z_increment': z_increment
        }
        self.program.append(op)
        return op
    
    def print_point(self, output_lines, x_next, y_next, z_current=None):
        if z_current is not None:
            output_lines.append("G1 X{:.4f} Y{:.4f} Z{:.4f}".format(x_next, y_next, z_current))
        else:
            output_lines.append("G1 X{:.4f} Y{:.4f}".format(x_next, y_next))
    
    def generate_circle(self, output_lines, rad, x_pos, y_pos, num_seg, z_offset=0):
        degrees_circle = 2 * pi
        x_start = float(x_pos)
        y_start = float(y_pos) + float(rad)
        x_next = x_start
        y_next = y_start
        deg_segment = degrees_circle / float(num_seg)
        deg_ind = 0.0
        
        z_current = z_offset
        self.print_point(output_lines, x_next, y_next, z_current)
        
        for i in range(0, int(num_seg)):
            deg_ind = deg_ind + deg_segment
            x_ind = float(rad) * sin(deg_ind)
            y_ind = float(rad) * cos(deg_ind)
            x_next = float(x_pos) + x_ind
            y_next = float(y_pos) + y_ind
            self.print_point(output_lines, x_next, y_next, z_current)
    
    def generate_line(self, output_lines, x_start, y_start, x_end, y_end, num_seg, z_offset=0):
        self.print_point(output_lines, x_start, y_start, z_offset)
        
        length = sqrt(pow(float(x_end) - float(x_start), 2) + pow(float(y_end) - float(y_start), 2))
        len_segment = length / float(num_seg)
        len_ind = 0
        
        x_dist = float(x_end) - float(x_start)
        y_dist = float(y_end) - float(y_start)
        alpha = atan2(y_dist, x_dist)
        
        z_current = z_offset
        for i in range(0, int(num_seg)):
            len_ind = len_ind + len_segment
            x_ind = float(len_ind) * cos(alpha)
            y_ind = float(len_ind) * sin(alpha)
            x_next = float(x_start) + x_ind
            y_next = float(y_start) + y_ind
            self.print_point(output_lines, x_next, y_next, z_current)
    
    def generate(self, write=False, filename=None):
        output_lines = []
        
        for op in self.program:
            if op['type'] == 'start_mcode':
                if op['speed'] is not None:
                    output_lines.append("{} S{}".format(op['code'], op['speed']))
                else:
                    output_lines.append(op['code'])
            
            elif op['type'] == 'end_mcode':
                output_lines.append(op['code'])
            
            elif op['type'] == 'circle':
                self.generate_circle(
                    output_lines,
                    op['rad'], op['x_pos'], op['y_pos'], op['num_seg']
                )
            
            elif op['type'] == 'line':
                self.generate_line(
                    output_lines,
                    op['x_start'], op['y_start'], op['x_end'], op['y_end'], op['num_seg']
                )
            
            elif op['type'] == 'iteration':
                shape_id = op['shape_id']
                count = op['count']
                z_increment = op['z_increment']
                
                shapes_to_iterate = [p for p in self.program if p['id'] == shape_id]
                if not shapes_to_iterate:
                    continue
                
                shape_op = shapes_to_iterate[0]
                
                for iter_idx in range(count):
                    z_offset = iter_idx * z_increment
                    
                    if shape_op['type'] == 'circle':
                        self.generate_circle(
                            output_lines,
                            shape_op['rad'], shape_op['x_pos'], shape_op['y_pos'],
                            shape_op['num_seg'], z_offset
                        )
                    elif shape_op['type'] == 'line':
                        self.generate_line(
                            output_lines,
                            shape_op['x_start'], shape_op['y_start'],
                            shape_op['x_end'], shape_op['y_end'],
                            shape_op['num_seg'], z_offset
                        )
        
        if write and filename:
            with open(filename, "w") as f:
                f.write("\n".join(output_lines))
            return None, filename
        else:
            return "\n".join(output_lines), None
    
    def get_shape_names(self):
        shapes = []
        for op in self.program:
            if op['type'] in ('circle', 'line'):
                shapes.append(op)
        return shapes
    
    def preview_program(self):
        lines = []
        for op in self.program:
            if op['type'] == 'start_mcode':
                if op['speed'] is not None:
                    lines.append("{}. Start M-Code: {} S{}".format(op['id'], op['code'], op['speed']))
                else:
                    lines.append("{}. Start M-Code: {}".format(op['id'], op['code']))
            elif op['type'] == 'end_mcode':
                lines.append("{}. End M-Code: {}".format(op['id'], op['code']))
            elif op['type'] == 'circle':
                lines.append("{}. Circle: radius={}, center=({}, {}), segments={}".format(
                    op['id'], op['rad'], op['x_pos'], op['y_pos'], op['num_seg']))
            elif op['type'] == 'line':
                lines.append("{}. Line: ({}, {}) to ({}, {}), segments={}".format(
                    op['id'], op['x_start'], op['y_start'], op['x_end'], op['y_end'], op['num_seg']))
            elif op['type'] == 'iteration':
                lines.append("{}. Iteration: shape #{}, count={}, z_increment={}".format(
                    op['id'], op['shape_id'], op['count'], op['z_increment']))
        return lines


def get_integer(prompt, min_val=None, max_val=None):
    while True:
        try:
            value = int(input(prompt))
            if min_val is not None and value < min_val:
                print("Value must be at least {}".format(min_val))
                continue
            if max_val is not None and value > max_val:
                print("Value must be at most {}".format(max_val))
                continue
            return value
        except ValueError:
            print("Please enter a valid integer.")


def get_float(prompt):
    while True:
        try:
            return float(input(prompt))
        except ValueError:
            print("Please enter a valid number.")


def get_menu_choice(prompt, valid_choices):
    while True:
        choice = input(prompt).strip().upper()
        if choice in valid_choices:
            return choice
        print("Invalid choice. Please enter: {}".format(", ".join(valid_choices)))


def show_main_menu(gen):
    print("\n" + "=" * 50)
    print("=== AxisEngine G-Code Generator ===")
    print("=" * 50)
    
    if gen.program:
        print("\nCurrent Program:")
        for line in gen.preview_program():
            print("  " + line)
    else:
        print("\nProgram is empty.")
    
    print("\nCommands:")
    print("  A) Add Start M-Code")
    print("  B) Add End M-Code")
    print("  C) Add Circle")
    print("  L) Add Line")
    print("  I) Add Iteration")
    print("  P) Preview Program")
    print("  G) Generate G-Code")
    print("  X) Clear Program")
    print("  Q) Quit")
    print("-" * 50)


def add_start_mcode(gen):
    print("\n--- Add Start M-Code ---")
    print("  1) M3 S<speed> (Spindle on, clockwise)")
    print("  2) M4 S<speed> (Spindle on, counter-clockwise)")
    print("  3) M8 (Coolant on)")
    print("  4) M9 (Coolant off)")
    print("  5) Custom")
    
    choice = get_menu_choice("Select M-Code (1-5): ", ['1', '2', '3', '4', '5'])
    
    if choice == '1':
        speed = get_integer("Enter spindle speed (e.g., 1000): ", 1)
        gen.add_start_mcode("M3", speed)
        print("Added: M3 S{}".format(speed))
    elif choice == '2':
        speed = get_integer("Enter spindle speed (e.g., 1000): ", 1)
        gen.add_start_mcode("M4", speed)
        print("Added: M4 S{}".format(speed))
    elif choice == '3':
        gen.add_start_mcode("M8")
        print("Added: M8")
    elif choice == '4':
        gen.add_start_mcode("M9")
        print("Added: M9")
    elif choice == '5':
        code = input("Enter M-Code (e.g., M3): ").strip()
        speed = None
        if 'S' in code.upper():
            try:
                speed_part = code.upper().split('S')[1].split()[0]
                speed = int(speed_part)
            except:
                pass
        gen.add_start_mcode(code, speed)
        print("Added: {}".format(code))


def add_end_mcode(gen):
    print("\n--- Add End M-Code ---")
    print("  1) M5 (Spindle off)")
    print("  2) M8 (Coolant on)")
    print("  3) M9 (Coolant off)")
    print("  4) Custom")
    
    choice = get_menu_choice("Select M-Code (1-4): ", ['1', '2', '3', '4'])
    
    if choice == '1':
        gen.add_end_mcode("M5")
        print("Added: M5")
    elif choice == '2':
        gen.add_end_mcode("M8")
        print("Added: M8")
    elif choice == '3':
        gen.add_end_mcode("M9")
        print("Added: M9")
    elif choice == '4':
        code = input("Enter M-Code (e.g., M5): ").strip()
        gen.add_end_mcode(code)
        print("Added: {}".format(code))


def add_circle(gen):
    print("\n--- Add Circle ---")
    rad = get_float("Enter radius: ")
    x_pos = get_float("Enter X center: ")
    y_pos = get_float("Enter Y center: ")
    num_seg = get_integer("Enter number of segments: ", 1)
    
    gen.add_circle(rad, x_pos, y_pos, num_seg)
    print("Added: Circle (radius={}, center=({}, {}), segments={})".format(
        rad, x_pos, y_pos, num_seg))


def add_line(gen):
    print("\n--- Add Line ---")
    x_start = get_float("Enter start X: ")
    y_start = get_float("Enter start Y: ")
    x_end = get_float("Enter end X: ")
    y_end = get_float("Enter end Y: ")
    num_seg = get_integer("Enter number of segments: ", 1)
    
    gen.add_line(x_start, y_start, x_end, y_end, num_seg)
    print("Added: Line from ({}, {}) to ({}, {}) with {} segments".format(
        x_start, y_start, x_end, y_end, num_seg))


def add_iteration(gen):
    shapes = gen.get_shape_names()
    if not shapes:
        print("\nNo shapes available to iterate. Add a circle or line first.")
        return
    
    print("\n--- Add Iteration ---")
    print("Available shapes:")
    for s in shapes:
        if s['type'] == 'circle':
            print("  #{} - Circle (radius={})".format(s['id'], s['rad']))
        elif s['type'] == 'line':
            print("  #{} - Line ({} to {})".format(s['id'], 
                (s['x_start'], s['y_start']), (s['x_end'], s['y_end'])))
    
    shape_id = get_integer("Enter shape ID to iterate: ")
    valid_ids = [s['id'] for s in shapes]
    if shape_id not in valid_ids:
        print("Invalid shape ID.")
        return
    
    count = get_integer("Enter number of iterations: ", 1)
    z_increment = get_float("Enter Z increment per iteration: ")
    
    gen.add_iteration(shape_id, count, z_increment)
    print("Added: Iteration of shape #{} ({} times, Z increment={})".format(
        shape_id, count, z_increment))


def generate_gcode(gen):
    if not gen.program:
        print("\nProgram is empty. Add operations first.")
        return
    
    print("\n--- Generate G-Code ---")
    print("  1) Print to console")
    print("  2) Save to file")
    
    choice = get_menu_choice("Select output (1-2): ", ['1', '2'])
    
    filename = None
    write = False
    
    if choice == '2':
        print("\nEnter filename (leave empty for auto-generated):")
        filename_input = input("Filename: ").strip()
        if filename_input:
            if not filename_input.endswith('.gcode'):
                filename_input += '.gcode'
            filename = os.path.join(GCODE_DIR, filename_input)
        else:
            for i in range(100):
                filename = os.path.join(GCODE_DIR, "generated{}.gcode".format(i))
                if not os.path.isfile(filename):
                    break
        write = True
        os.makedirs(GCODE_DIR, exist_ok=True)
    
    output, saved_to = gen.generate(write=write, filename=filename)
    
    if output:
        print("\n" + "=" * 50)
        print("Generated G-Code:")
        print("=" * 50)
        print(output)
        print("=" * 50)
    
    if saved_to:
        print("\nSaved to: {}".format(saved_to))


def main():
    gen = GCodeGenerator()
    
    while True:
        show_main_menu(gen)
        choice = get_menu_choice("Select command: ", 
            ['A', 'B', 'C', 'L', 'I', 'P', 'G', 'X', 'Q'])
        
        if choice == 'A':
            add_start_mcode(gen)
        elif choice == 'B':
            add_end_mcode(gen)
        elif choice == 'C':
            add_circle(gen)
        elif choice == 'L':
            add_line(gen)
        elif choice == 'I':
            add_iteration(gen)
        elif choice == 'P':
            print("\n--- Program Preview ---")
            if gen.program:
                for line in gen.preview_program():
                    print("  " + line)
            else:
                print("  (empty)")
        elif choice == 'G':
            generate_gcode(gen)
        elif choice == 'X':
            gen.clear_program()
            print("\nProgram cleared.")
        elif choice == 'Q':
            print("\nGoodbye!")
            break


if __name__ == "__main__":
    main()
