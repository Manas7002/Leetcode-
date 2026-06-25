import os

# Directories and file types to track
categories = ['arrays', 'strings', 'linked-lists', 'trees', 'dp', 'graphs']
extensions = ('.py', '.c', '.cpp')

total_count = 0
stats = {}

# Scan folders and count solution files
for folder in categories:
    if os.path.exists(folder):
        count = sum(1 for f in os.listdir(folder) if f.endswith(extensions))
        stats[folder.capitalize()] = count
        total_count += count
    else:
        stats[folder.capitalize()] = 0

# Format the markdown output
md_content = f"# LeetCode Progress\n\n**Total Problems Solved:** {total_count}\n\n"
md_content += "| Category | Solved |\n| --- | --- |\n"

for cat, count in stats.items():
    md_content += f"| {cat} | {count} |\n"

# Write directly to progress.md
with open('progress.md', 'w') as f:
    f.write(md_content)
    
print("Successfully updated progress.md!")
