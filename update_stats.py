import os
import re

def count_difficulties():
    easy, medium, hard = 0, 0, 0
    
    # Iterate through all directories in the repo
    for root, dirs, files in os.walk("."):
        # Look specifically inside the LeetHub problem folders for their README.md
        if "README.md" in files and root != ".":
            readme_path = os.path.join(root, "README.md")
            try:
                with open(readme_path, "r", encoding="utf-8") as f:
                    content = f.read()
                    # LeetHub adds the difficulty directly in the parsed markdown text
                    if re.search(r"\bEasy\b", content, re.IGNORECASE):
                        easy += 1
                    elif re.search(r"\bMedium\b", content, re.IGNORECASE):
                        medium += 1
                    elif re.search(r"\bHard\b", content, re.IGNORECASE):
                        hard += 1
            except Exception:
                pass
                
    return easy, medium, hard

def update_readme(easy, medium, hard):
    total = easy + medium + hard
    stats_markdown = f"""
### 📊 LeetCode Progress Dashboard

| Difficulty | Solved Count |
| :--- | :--- |
| 🟢 **Easy** | {easy} |
| 🟡 **Medium** | {medium} |
| 🔴 **Hard** | {hard} |
| 🔢 **Total** | **{total}** |

_Last Updated automatically via update_stats.py_
"""
    
    with open("README.md", "r", encoding="utf-8") as f:
        readme_content = f.read()

    # Replace old stats block if it exists, otherwise append it
    pattern = r".*?"
    if re.search(pattern, readme_content, re.DOTALL):
        new_content = re.sub(pattern, stats_markdown.strip(), readme_content, flags=re.DOTALL)
    else:
        new_content = readme_content + "\n" + stats_markdown

    with open("README.md", "w", encoding="utf-8") as f:
        f.write(new_content)

if __name__ == "__main__":
    e, m, h = count_difficulties()
    update_readme(e, m, h)
    print(f"Stats updated! Easy: {e}, Medium: {m}, Hard: {h}")